#pragma save_binary



string word_wrap_with_paragraphs(string str)
{
  string *paragraphs;
  int i;

  if (!str) 
    return 0;
  paragraphs = explode(str, "\n");
  for (i = 0; i < sizeof(paragraphs); i++) 
    if (i) 
      paragraphs[i] = break_string("  " + paragraphs[i], 70);
    else
      paragraphs[i] = break_string(paragraphs[i], 70);
  
  return implode(paragraphs, "\n") + "\n";
}



int word_in(string word, string str)
{
  string a, b;

  str  = lower_case(str);
  word = lower_case(word);

  if (word == str)
    return 1;

  if (sscanf(" " + str + " ", "%s" + word + "%s", a, b) == 2) {
    if (a[strlen(a) -  1] < '0' &&
	b[0]              <'0')
      return 1;
    else 
      return word_in(word, b);
  }

  return 0;
}
