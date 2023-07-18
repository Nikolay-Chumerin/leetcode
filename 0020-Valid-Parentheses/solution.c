bool isValid(char *s) {
  bool ok = true;
  char *stack = s;
  int stack_idx = 0;
  while (ok && *s) {
    const unsigned char c = *s++;
    if (c == '(' || c == '[' || c == '{') {
      stack[stack_idx++] = c; // push c to stack...
    } else {
      if (stack_idx < 1) {
        ok = false;
      } else {
        // Normal version:
        // const unsigned char pc = stack[--stack_idx];  // pop from stack
        // if ( (c==')' && pc!='(') || (c=='}' && pc!='{') || (c==']' &&
        // pc!='[')) {
        //     ok = false;
        // }

        // Hacky-version: '{' ^ '}' == '[' ^ ']' == 6, '(' ^ ')' == 1
        const unsigned char xc = c ^ stack[--stack_idx]; // xor with stack top
        ok = (xc == 1) || (xc == 6);
      } // stack not empty branch
    }   //  open/close brcket branch
  }     // loop
  ok &= (stack_idx == 0);
  return ok;
}
