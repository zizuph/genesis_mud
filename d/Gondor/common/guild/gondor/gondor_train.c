/*
 *   Rangers of Gondor training hall - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   The train hall of Gondor Company
 *   Modified by Olorin, 30-Oct-1993
 *   
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/ranger_train.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* A few definitions */
#define COMPANY_NO   1   /* The Gondor Company is no 1 */

void 
create_trainhall() 
{ 
    company_no = COMPANY_NO;

    set_short("Rangers of Gondor Training Hall");
    set_long("This is the Rangers of Gondor training hall.\n"+
        BSN("By the south wall is a large pool from which a fog is rising, " +
        "filling the hall with the smell of herbs. You may <enter> this pool, "+
        "and redefine your personal priorities. You may also <learn> new "+
        "skills, or <improve> the skills you already have, " +
        "and you may <list guilds> to discover information about " +
        "the guilds of which you are a member. " +
        "On the wall behind the damping pool you see a relief of the "+
        "White Tree. On a poster next to the relief you can see to which " +
        "level you can train skills here if you are one of the Rangers of Gondor. ") +
        "A doorway leads north to the bulletin board hall.\n");
    add_exit(RANGER_GON_DIR + "boardhall", "north", 0, 0);
    add_prop(ROOM_M_NO_STEAL, no_theft);

    add_item("pool",BSN(
        "The pool is filled with hot water and herbs, spreading a special "+
        "odour in the hall. "));
    add_item(({"master ranger","ranger"}), BSN(
	"This is one of the veteran rangers who have retired from adventuring, "+
	"and have decided to found and run this guild. "));
    add_item( ({ "tree", "white tree", "relief", }), BSN(
      "This is a relief of the White Tree of Gondor, " +
      "standing in the Citadel of Minas Anor, where Isildur planted it " +
      "in memory of his brother Anarion. The relief shows the White " +
      "Tree in full bloom and manages to catch the beauty and power " +
      "of the White Tree admirably."));
}

void 
enter_inv(object ob, object from) 
{
  ::enter_inv(ob, from);
    
  if (!interactive(ob) || !closed)
    return;
    
  if (ob->query_wiz_level()) 
    write("\n\nWARNING!\nYou shouldn't be here. "+
          "I'm doing some work on the guild.\n");
  else {
    write("The guild is closed. Come back later.\n");
    ob->move(RANGER_GON_DIR+"boardhall");
  }
}
