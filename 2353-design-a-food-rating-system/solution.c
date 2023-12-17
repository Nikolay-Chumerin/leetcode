/*
 * @lc app=leetcode id=2353 lang=c
 *
 * [2353] Design a Food Rating System
 *
 * https://leetcode.com/problems/design-a-food-rating-system/description/
 *
 * algorithms
 * Medium (34.50%)
 * Likes:    1308
 * Dislikes: 268
 * Total Accepted:    70.4K
 * Total Submissions: 152K
 * Testcase Example:
 '["FoodRatings","highestRated","highestRated","changeRating","highestRated","changeRating","highestRated"]\n'
 +
  '[[["kimchi","miso","sushi","moussaka","ramen","bulgogi"],["korean","japanese","japanese","greek","japanese","korean"],[9,12,8,15,14,7]],["korean"],["japanese"],["sushi",16],["japanese"],["ramen",16],["japanese"]]'
 *
 * Design a food rating system that can do the following:
 *
 *
 * Modify the rating of a food item listed in the system.
 * Return the highest-rated food item for a type of cuisine in the system.
 *
 *
 * Implement the FoodRatings class:
 *
 *
 * FoodRatings(String[] foods, String[] cuisines, int[] ratings) Initializes
 * the system. The food items are described by foods, cuisines and ratings, all
 * of which have a length of n.
 *
 *
 * foods[i] is the name of the i^th food,
 * cuisines[i] is the type of cuisine of the i^th food, and
 * ratings[i] is the initial rating of the i^th food.
 *
 *
 * void changeRating(String food, int newRating) Changes the rating of the food
 * item with the name food.
 * String highestRated(String cuisine) Returns the name of the food item that
 * has the highest rating for the given type of cuisine. If there is a tie,
 * return the item with the lexicographically smaller name.
 *
 *
 * Note that a string x is lexicographically smaller than string y if x comes
 * before y in dictionary order, that is, either x is a prefix of y, or if i is
 * the first position such that x[i] != y[i], then x[i] comes before y[i] in
 * alphabetic order.
 *
 *
 * Example 1:
 *
 *
 * Input
 * ["FoodRatings", "highestRated", "highestRated", "changeRating",
 * "highestRated", "changeRating", "highestRated"]
 * [[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean",
 * "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14,
 * 7]], ["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16],
 * ["japanese"]]
 * Output
 * [null, "kimchi", "ramen", null, "sushi", null, "ramen"]
 *
 * Explanation
 * FoodRatings foodRatings = new FoodRatings(["kimchi", "miso", "sushi",
 * "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek",
 * "japanese", "korean"], [9, 12, 8, 15, 14, 7]);
 * foodRatings.highestRated("korean"); // return "kimchi"
 * ⁠                                   // "kimchi" is the highest rated korean
 * food with a rating of 9.
 * foodRatings.highestRated("japanese"); // return "ramen"
 * ⁠                                     // "ramen" is the highest rated
 * japanese food with a rating of 14.
 * foodRatings.changeRating("sushi", 16); // "sushi" now has a rating of 16.
 * foodRatings.highestRated("japanese"); // return "sushi"
 * ⁠                                     // "sushi" is the highest rated
 * japanese food with a rating of 16.
 * foodRatings.changeRating("ramen", 16); // "ramen" now has a rating of 16.
 * foodRatings.highestRated("japanese"); // return "ramen"
 * ⁠                                     // Both "sushi" and "ramen" have a
 * rating of 16.
 * ⁠                                     // However, "ramen" is
 * lexicographically smaller than "sushi".
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 2 * 10^4
 * n == foods.length == cuisines.length == ratings.length
 * 1 <= foods[i].length, cuisines[i].length <= 10
 * foods[i], cuisines[i] consist of lowercase English letters.
 * 1 <= ratings[i] <= 10^8
 * All the strings in foods are distinct.
 * food will be the name of a food item in the system across all calls to
 * changeRating.
 * cuisine will be a type of cuisine of at least one food item in the system
 * across all calls to highestRated.
 * At most 2 * 10^4 calls in total will be made to changeRating and
 * highestRated.
 *
 *
 */

// @lc code=start
typedef uint64_t hash_t;

static hash_t hash(const char* cp) {
  hash_t hash = 5381;
  while (*cp) hash = 33 * hash ^ (unsigned char)*cp++;
  return hash;
}

typedef struct {
  char* food;
  char* cuisine;
  int rating;
  hash_t food_hash;
  hash_t cuisine_hash;
} FoodRating;

typedef struct {
  FoodRating* data;
  int size;
} FoodRatings;

FoodRatings* foodRatingsCreate(char** foods, int foodsSize, char** cuisines,
                               int cuisinesSize, int* ratings,
                               int ratingsSize) {
  FoodRatings* fr = malloc(sizeof(FoodRatings));
  fr->size = foodsSize;
  fr->data = calloc(sizeof(FoodRating), fr->size);
  for (int i = 0; i < fr->size; ++i) {
    fr->data[i] = (FoodRating){.food = foods[i],
                               .cuisine = cuisines[i],
                               .rating = ratings[i],
                               .food_hash = hash(foods[i]),
                               .cuisine_hash = hash(cuisines[i])};
  }
  return fr;
}

int foodRatingsFoodIdx(const FoodRatings* obj, const char* food) {
  const hash_t food_hash = hash(food);
  for (int i = 0; i < obj->size; ++i) {
    const FoodRating* fr = &obj->data[i];
    if (food_hash == fr->food_hash) {
      return i;
    }
  }
  return -1;
}

void foodRatingsChangeRating(FoodRatings* obj, char* food, int newRating) {
  int idx = foodRatingsFoodIdx(obj, food);
  obj->data[idx].rating = newRating;
}

char* foodRatingsHighestRated(const FoodRatings* obj, const char* cuisine) {
  const hash_t cuisine_hash = hash(cuisine);
  int max_rating = 0;
  char* ans = NULL;
  for (int i = 0; i < obj->size; ++i) {
    const FoodRating* fr = &obj->data[i];
    if (cuisine_hash == fr->cuisine_hash && max_rating <= fr->rating) {
      if (max_rating == fr->rating && strcmp(ans, fr->food) < 0) continue;
      max_rating = fr->rating;
      ans = fr->food;
    }
  }
  return ans;
}

void foodRatingsFree(FoodRatings* obj) {
  if (!obj) return;
  free(obj->data);
}

/**
 * Your FoodRatings struct will be instantiated and called as such:
 * FoodRatings* obj = foodRatingsCreate(foods, foodsSize, cuisines,
 cuisinesSize, ratings, ratingsSize);
 * foodRatingsChangeRating(obj, food, newRating);

 * char* param_2 = foodRatingsHighestRated(obj, cuisine);

 * foodRatingsFree(obj);
*/
// @lc code=end
