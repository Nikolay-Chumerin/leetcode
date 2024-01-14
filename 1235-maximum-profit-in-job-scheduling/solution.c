/*
 * @lc app=leetcode id=1235 lang=c
 *
 * [1235] Maximum Profit in Job Scheduling
 *
 * https://leetcode.com/problems/maximum-job_profits-in-job-scheduling/description/
 *
 * algorithms
 * Hard (53.35%)
 * Likes:    6607
 * Dislikes: 98
 * Total Accepted:    283.3K
 * Total Submissions: 516.5K
 * Testcase Example:  '[1,2,3,3]\n[3,4,5,6]\n[50,10,40,70]'
 *
 * We have n jobs, where every job is scheduled to be done from job_starts[i] to
 * job_ends[i], obtaining a job_profits of job_profits[i].
 *
 * You're given the job_starts, job_ends and job_profits arrays, return the
 * maximum job_profits you can take such that there are no two jobs in the
 * subset with overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another
 * job that starts at time X.
 *
 *
 * Example 1:
 *
 *
 *
 *
 * Input: job_starts = [1,2,3,3], job_ends = [3,4,5,6], job_profits =
 * [50,10,40,70] Output: 120 Explanation: The subset chosen is the first and
 * fourth job. Time range [1-3]+[3-6] , we get job_profits of 120 = 50 + 70.
 *
 *
 * Example 2:
 *
 * ⁠
 *
 *
 * Input: job_starts = [1,2,3,4,6], job_ends = [3,5,10,6,9], job_profits =
 * [20,20,100,70,60]
 * Output: 150
 * Explanation: The subset chosen is the first, fourth and fifth job.
 * Profit obtained 150 = 20 + 70 + 60.
 *
 *
 * Example 3:
 *
 *
 *
 *
 * Input: job_starts = [1,1,1], job_ends = [2,3,4], job_profits = [5,6,4]
 * Output: 6
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= job_starts.length == job_ends.length == job_profits.length <= 5 * 10^4
 * 1 <= job_starts[i] < job_ends[i] <= 10^9
 * 1 <= job_profits[i] <= 10^4
 *
 *
 */

// @lc code=start
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize(-flto, -ffast - math, -march = native, -mtune = native)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Dynamic Programming solution */
typedef struct {
  int start;
  int end;
  int profit;
} job_t;

int compare_jobs_by_end(const void* a, const void* b) {
  return ((job_t*)a)->end - ((job_t*)b)->end;
}

int find_best_prev_job(job_t* jobs, const int n, const int max_end,
                       const int max_idx) {
  int left_idx = 0, right_idx = max_idx;
  while (left_idx < right_idx) {
    const int mid_idx = (left_idx + right_idx) / 2;
    if (jobs[mid_idx].end > max_end) {
      right_idx = mid_idx;
    } else {
      left_idx = mid_idx + 1;
    }
  }
  return left_idx - 1;  // can be -1, which is handled well later
}  // find_best_prev_job(....)

int jobScheduling(int* job_starts, int starts_num, int* job_ends, int ends_num,
                  int* job_profits, int profits_num) {
  const int n = starts_num;
  job_t jobs[n];
  for (int i = 0; i < n; ++i) {
    jobs[i].start = job_starts[i];
    jobs[i].end = job_ends[i];
    jobs[i].profit = job_profits[i];
  }
  qsort(jobs, n, sizeof(job_t), compare_jobs_by_end);

  int profits[n + 1];
  profits[0] = 0;

  for (int i = 0; i < n; ++i) {
    const int prev_job_idx = find_best_prev_job(jobs, n, jobs[i].start, i);
    const int candidate_profit = jobs[i].profit + profits[prev_job_idx + 1];
    profits[i + 1] = MAX(profits[i], candidate_profit);
  }  // loop over sorted (be end) jobs
  return profits[n];
}  // jobScheduling(....)

/*
Backtracking solution

#include <sys/time.h>

#define MAX_EXECUTION_TIME_US (2210000)

typedef struct {
  int start;
  int end;
  int job_profits;
  int next_start_idx;
} job_t;

int compare_jobs(const void* a, const void* b) {
  return ((job_t*) a)->start - ((job_t*) b)->start;
}

void print_jobs(const job_t jobs[], const int jobs_num) {
  puts("jobs:");
  for (int i = 0; i < jobs_num; ++i) {
    printf("i=%-5d start=%-4d  end=%-4d job_profits=%-4d next_start_idx=%-4d\n",
i, jobs[i].start, jobs[i].end, jobs[i].job_profits, jobs[i].next_start_idx);
  }
}

void fill_next_start_indices(job_t* jobs, const int n) {
  for (int i = 0; i < n; ++i) {
    const int minimal_start_time = jobs[i].end;
    for (int j = i + 1; j < n; ++j) {
      if (minimal_start_time <= jobs[j].start) {
        jobs[i].next_start_idx = j;
        break;
      }  // found first well fitting job branch
    }  // next idx search loop
  }  // main i-loop
}  // fill_next_start_indices(..)

void print_state(const int* stack, const int stack_sz, const int next_start_idx,
const int curr_profit) { printf("curr_profit=%d next_start_idx=%d stack=[ ",
curr_profit, next_start_idx); for (int i = 0; i < stack_sz; ++i) printf("%d ",
stack[i]); printf("]\n"); }  // print_state(....)

int jobScheduling(int* job_starts, int starts_num, int* job_ends, int
ends_num, int* job_profits, int profits_num) {

  struct timeval stop, start;
  gettimeofday(&start, NULL);

  const int n = starts_num;
  // printf("---[ n = %d ]---------\n", n);
  job_t jobs[n];
  for (int i = 0; i < n; ++i) {
    jobs[i].start = job_starts[i];
    jobs[i].end = job_ends[i];
    jobs[i].job_profits = job_profits[i];
    jobs[i].next_start_idx = -1;
  }
  qsort(jobs, n, sizeof(job_t), compare_jobs);
  fill_next_start_indices(jobs, n);
  // print_jobs(jobs, n);

  int stack[n];
  int stack_sz = 0;

  int idx = 0;
  stack[stack_sz++] = idx;
  int curr_profit = jobs[idx].job_profits;
  int ans = curr_profit;
  int next_start_idx = jobs[stack[stack_sz-1]].next_start_idx;
  int last_end;
  while (stack_sz > 0) {
    // puts("---");
    // next_start_idx = jobs[stack[stack_sz-1]].next_start_idx;
    last_end = jobs[stack[stack_sz-1]].end;
    // printf("next_start_idx=%d\n", next_start_idx);
    if (next_start_idx >= 0) {
      // search for the next fitting job
      idx = next_start_idx;
      while (idx < n) {
        if (last_end <= jobs[idx].start) { // if job is found:
          // 1) update current job_profits, 2) push its idx on stack, 3) update
next_start_idx
          // printf("push job#%d [start=%d end=%d job_profits=%d]
job_profits=%d->",
          //        idx, jobs[idx].start, jobs[idx].end, jobs[idx].job_profits,
curr_profit); curr_profit += jobs[idx].job_profits;
          // printf("%d next_start_idx=%d->", curr_profit, next_start_idx);
          next_start_idx = jobs[idx].next_start_idx;
          last_end = jobs[idx].end;
          // printf("%d\n",next_start_idx);
          stack[stack_sz++] = idx;
          // print_state(stack, stack_sz, next_start_idx, curr_profit);
          if (next_start_idx < 0) {
            // puts("breaking...");
            break;
          }
        }
        ++idx;
      }  // idx-loop
    }  // if (next_start_idx >= 0)
    // print_state(stack, stack_sz, next_start_idx, curr_profit);
    if (ans < curr_profit) {
      // printf("ans=%d -> %d\n", ans, curr_profit);
      ans = curr_profit;
      // printf("ans=%d\n", ans);
      // printf("took %lu us\n", );
    }
    gettimeofday(&stop, NULL);
    const size_t dt = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec -
start.tv_usec; if (dt >= MAX_EXECUTION_TIME_US) return ans;

    // pop from stack previous idx, increment it and try to continue..
    if (next_start_idx < 0) {
      do {
        idx = stack[--stack_sz];
        // printf("pop job#%d [start=%d end=%d job_profits=%d]
job_profits=%d->",
        //         idx, jobs[idx].start, jobs[idx].end, jobs[idx].job_profits,
curr_profit); curr_profit -= jobs[idx].job_profits; last_end = jobs[idx].end;
        // printf("%d idx=%d->%d\n", curr_profit, idx, idx + 1);
        ++idx;
        if (stack_sz >= 0 && idx < n) break;
      } while (stack_sz > 0);
      next_start_idx = idx;
    }  // if (next_start_idx < 0)

    if (stack_sz == 0 && idx < n) {
      // printf("push job#%d [start=%d end=%d job_profits=%d] job_profits=%d->",
      //         idx, jobs[idx].start, jobs[idx].end, jobs[idx].job_profits,
curr_profit); curr_profit += jobs[idx].job_profits; stack[stack_sz++] = idx;
      next_start_idx = jobs[idx].next_start_idx;
      // printf("%d", curr_profit);
    }
  }  // main loop

  return ans;
}
*/
// @lc code=end
