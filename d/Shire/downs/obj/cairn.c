/*
 * Cairn for the Barrow Downs
 * Original concept and area by Dondon, October 1993
 * Expanded and enlarged by Finwe, December 2001
 */

inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

/*
 *  The replacement characters are randomly picked from this string.
 *  It must be 100 characters long.
 */
#define MISS_STR "anvvicwmjfdoqqpaeirnxzaesldkfyvoxpeorrjdfrfdtsafmdktfaqdfdejwefwapdveelrezzqrjewsdfsgfdcxfdfkefepeol"

create_object()
{
    set_name(({"cairn","monument","marker"}));
    set_adj("bone");
    set_adj("white");
    set_short("bone white cairn");
    set_long("The "+short()+" is a marker erected upon one of the graves " +
        "of the ancient King of Men. People have always been warned " +
        "to stay away from the cairns. There is some kind of inscription " +
        "in runes on the marker.\n");

    add_item(({"inscription", "runes"}),
    "The inscription is written in an ancient tongue.\n");

    add_prop(OBJ_I_NO_GET, "The "+short()+" is buried in the ground " +
        "and cannot be taken.\n");
}

init() {
    add_action("do_read","read",0);
    add_action("do_read","decipher",0);
}

do_read(str) {
    string text;

    if (str == "inscription" || str == "runes")
    {
	text = "You are able to make this out:\n\n"
	    +  scramble("\tFrom earth the rock in time was born.\n"
		      + "\tIt will still stand when man is torn.\n"
		      + "\tFrom man the treasure's rocks conceal.\n"
		      + "\tUnless from earth you it reveal.\n\n",
                        100 - 3*this_player()->query_skill(SS_LANGUAGE));
	write(text);
	say(QCTNAME(this_player()) + " tries to decipher the runes.\n");
	return 1;
    }
}


/*
 *  Scramble the text, dependent on a chance in percent
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
