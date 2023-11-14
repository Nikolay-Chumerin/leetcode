# Intuition
First thought was to isolate vowels and sort them as separate array, this works, but some (specially designed) tests are faling due to the time limit. Modifying `comparison()` function for `qsort()` is not so straight forward.
The number of vowels is just 10 (5 upper + 5 lower case), so we actually don't need to sort them, just count (which, effectively, is the counting sorting method).

# Approach
Count how many each vowel appears in the string.
Then pass through the input string and replace the first `char_counts['A']` number of vowels with 'A', then do the same with wovels 'E', 'I' and so on. No need to sort them, as it's done naturally while counting.

# Complexity
- Time complexity: $$O(n)$$
- Space complexity: $$O(1)$$

# Code
```
char *sortVowels(char *s) {
  char vowels[] = "AEIOUaeiou";
  const int vowels_num = 10;
  bool is_vowel[256];
  memset(is_vowel, 0, sizeof(is_vowel));
  for (int i = 0; i < vowels_num; ++i)
    is_vowel[vowels[i]] = true;

  int char_counts[256];
  memset(char_counts, 0, sizeof(char_counts));
  const int l = strlen(s);
  for (int i = 0; i < l; ++i)
    if (is_vowel[s[i]])
      ++char_counts[s[i]];

  int j = 0;
  for (int i = 0; j < l && i < vowels_num; ++i) {
    const char vowel = vowels[i];
    int vowel_count = char_counts[vowel];
    while (vowel_count && (j < l)) {
      if (is_vowel[s[j]]) {
        s[j] = vowel;
        --vowel_count;
      }
      ++j;
    }
  }
  return s;
}

```