/*
** Copy of Rohim's intro.c, recoded by Zima (3/9/98) for silent monks
** Refactored by Tapakah 08/2021
*/

#pragma no_clone
#pragma strict_types
#include <stdproperties.h>
 
void
showvow ()
{
  command("emote covers his mouth with his hand symbolizing his vow of "+
          "silence.");
}
void
hook_return_intro_new (string name) {
  if (!find_player(lower_case(name)))
    return; 
  command("bow " + name);
  showvow();
}

void introduce (string name) 
{ 
  return;
}
/*
void
add_introduced (string name) { greet(name); }
*/
string 
defans () {
   showvow();
   return "";
}
