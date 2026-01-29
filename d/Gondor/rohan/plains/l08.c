/*
 *  Modified by Alto, 10 June 2001
 *    Added exit to Fangorn Forest
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define RHARD		6

static object		Snake;
object *inv;

public int      check_ent_kill();

public void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("high thick green");
    set_land("the West Emnet");
    set_where("central");
    set_special(1);
    set_river_name("Deeping Stream");
    set_rhard(RHARD);
    set_rwhere("north");

   /* Now open to Fangorn Forest */

    add_exit("/d/Gondor/fangorn/fangorn33", "north", check_ent_kill, 0, 5);

    add_exit("l09","east",      0,     5);
/*
    add_exit("NotOpen/m08","north",crossing);
*/
    add_exit("k08","south",     0,     5);
    add_exit("l07","west",      0,     5);

    set_extraline("In a hollow, the green grass is replaced by yellow "
      + "sedge. Hidden in it, you can make out a small pool. To the north, "
      + "you see the dark edge of Fangorn Forest. ");

    add_item(({"water","pool","hollow","sedge"}), BSN(
        "The pool is almost completely hidden by the high sedge. It is "
      + "small, only about five meters in diameter. The water is dark "
      + "and smelly. There is quite a lot of mud surrounding the pool."));

    add_item(({"mud"}), BSN(
        "This mud looks very thick and soft. Some tales tell of soil"
      + " which when wet can cure minor rashes and insect bites when"
      + " rubbed on the skin. Perhaps this mud is of that variety."));

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE,ROOM_BEACH);
    

    reset_room();

    set_drink_from( ({"pool","stream","river","deeping stream"}) );
}

public int
drown()
{
   if (SECURITY->query_wiz_dom(TP->query_real_name()) == "Gondor")
   {
      write("This river is still closed for mortals, Wizard of Gondor!\n");
      return crossing();
   }
   write("The ford is closed by order of Theoden King, "+
	 "First Marshal of the Mark!\n");
   return 1;
}

public void
reset_room()
{
    ::reset_room();
    if (!objectp(Snake))
    {
	Snake = clone_npc(Snake, (NPC_DIR + "snake"));
	Snake->set_poison_file(POISON_DIR + "weak_snake_poison");
    }
}

public int
rub_mud(string str)
{
    object  poison,
	    tp = TP;
    string  where;

    if (!strlen(str))
    {
        NFN("Rub what?");
        return 0;
    }

    if (!(parse_command(str, ({ }),
        " 'mud' 'on' / 'onto' [my] 'skin' / 'bite' / 'bites' / "+
	"'itch' / 'itches' / 'rash' / 'body' / 'myself' / 'me'")))
    {
        NFN("Rub the mud where? On your skin?");
        return 0;
    }

    if (objectp(poison = present("poison", tp)))
    {
        if (strlen(where = poison->query_body_part()))
        {
            WRITE("You scoop some mud from the pool and rub it carefully "
              + "on the skin on your "+where+".");
            SAY(" scoops some mud from the pond and rubs"
              + " it carefully on the skin on "+POSSESSIVE(tp)
	      + " "+where+".");
        }
        else
        {
            write("You scoop some mud from the pool and rub it on "
	        + "your skin.\n");
            say(QCTNAME(tp) + " scoops some mud from the pond and rubs "
              + "it on "+POSSESSIVE(tp)+" skin.\n");
        }
        poison->cure_poison(({"mosquito"}), 50);
        poison->cure_poison(({"sumac"}), 50);
    }
    else
    {
        write("You scoop some mud from the pool and rub it on your skin.\n");
        say(QCTNAME(tp) + " scoops some mud from the pond and rubs"
          + " it on "+POSSESSIVE(tp)+" skin.\n");
    }

/* This is not the way to cure a poison!
    if (poison = present("mosquito_poison", TP))
    {
        poison->remove_object();
        return 1;
    }
 */

    return 1;
}

public int
check_ent_kill()
{
    inv = deep_inventory(TP);

    if (sizeof(filter(inv, &->id("torch"))))
    {
        write("The trees at the forest edge seem to move together to "
            + "prevent your passage. Perhaps they feel you might "
            + "accidentally start a forest fire.\n");
        return 1;
    }

    
    return 0;
}

void
init()
{
    ::init();
    add_action(rub_mud, "rub");
}
