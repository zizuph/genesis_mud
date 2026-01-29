inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

create_object() {
    set_name(({"barrow","rock"}));
    set_adj("black");
    set_short("barrow");
    set_long(break_string(
	  "The barrow is a black, obelisk-shaped rock that was erected "
	+ "here upon the grave of the men of ancient. People have always "
	+ "been warned to stay away from them. There is some kind of "
	+ "inscription in runes on the barrow.\n",70));

    add_item("inscription", "The inscription is written in runes.\n");

    add_prop(OBJ_I_NO_GET, 1);
}

init() {
    add_action("do_read","read",0);
    add_action("do_read","decipher",0);
}

do_read(str) {
    string text;

    if (str == "inscription" || str == "runes")
    {
	text = "You are able to make this out:\n"
	    +  scramble("From earth the rock in time was born.\n"
		      + "It will still stand when man is torn.\n"
		      + "From man the treasures rocks conceal.\n"
		      + "Unless from earth you it reveal.\n",
                        100 - 3*this_player()->query_skill(SS_LANGUAGE));
	write(text);
	say(QCTNAME(this_player()) + " tries to decipher the runes.\n");
	return 1;
    }
}

/*
 *  The replacement characters are randomly picked from this string.
 *  It must be 100 characters long.
 */
#define MISS_STR "anvvicwmjfdoqqpaeirnxzaesldkfyvoxpeorrjdfrfdtsafmdktfaqdfdejwefwapdveelrezzqrjewsdfsgfdcxfdfkefepeol"

/*
 *  Scramble a text, dependent on a chance in percent
 */
scramble(string text,int chance) {
   int len, i, ran;
   string char;

   text = " " + text  + " ";
   len = strlen(text);

   for (i=1; i<len-1; i++)
   {
      /* Leave newlines intact */
      if (chance > (ran = random(100)))
      {
         if ((char = extract(text,i,i)) != " " && char != "\n")
         {
            text = extract(text,0,i-1) + extract(MISS_STR,ran,ran)
                 + extract(text,i+1,len-1);
         }
      }
   }
   return extract(text,1,len-2);
}
