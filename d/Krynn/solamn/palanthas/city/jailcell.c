/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

#include <composite.h>
#define OFFICE15 "/d/Krynn/solamn/palanthas/city/jailfoyer"


/* idea: a person who is starting a fight in Palanthas will be dragged
 *       to the judge, sentenced for disturbing the peace to 2 days
 *       (1500 seconds!) of prison. If he contacts a friend who
 *       pays a fee of 1 platinum coin, ---
 *       the person will be released again, before the time is up.
 *       to do this, the other person has to get a form fill it in
 *       get signatures from judge, archive, and treasury (pay there!)
 *       give the form to the chief guard and he will release the 
 *       prisoner. (if he's not there he can't release! ;-)
 */

void
create_palan_room()
{
    set_short("Jail");
    set_long("@@my_long");

    OUTSIDE;/*hmm, to allow pigeons in here */
    LIGHT;

    add_prop(MAGIC_AM_MAGIC,({30, "enchantment"}));
    add_prop(ROOM_M_NO_TELEPORT, "You get the impression that this is a "
          +  "real jail, and a very good one at that; one that jails "
          +  "in every dimension!\n");
	add_prop(ROOM_M_NO_ATTACK, "You are already in jail.  Violating the "
	+ "law here is likely to get you executed on the spot.\n");

    clone_object(OBJ + "jaildoorj")->move(TO);

    add_item("sign","The sign says: You are allowed to communicate with "
          +  "friends.\n");
}


init()
{
  ::init();
  ADA("read");
}


read(string str)
{
  if (!str)
    return 0;
  if (str != "sign")
    return 0;
  write("The sign says: You are allowed to communicate with "
          +  "friends.\n");
  return 1;
}


string
who_is_outside()
{
  object *things;
  string pers;
  object ja;
  OFFICE15->load_me();
  ja = find_object(OFFICE15);
  things = all_inventory(ja);
  pers = COMPOSITE_LIVE(things);
  if (pers == "someone")
    return "The office to your south is completely empty at the moment.";
  return "You can see " + pers + " in the office to your south.";
}

string
my_long()
{
  string pers = who_is_outside();
  return "This is the Jail. There is no escape! The room is made "
       + "from huge stone blocks, only a small window high up in one "
	   + "wall lets in some light and air. There is a small sign on the "
       + "west wall. " + pers;
}
