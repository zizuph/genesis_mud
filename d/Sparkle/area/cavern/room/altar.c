
/* altar.c
 * Written by Quis for the Goblin Start Area 920516
 */

/*   
 * I stole the meditation support 
 * /Quis 8)
 *
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *           /Styles.
 *
 * Updated the 'pray' routine to conform with current
 * ghost handling standards, Dec 9/96 - Khail.
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/guild_support"; 

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <language.h>
#include "/d/Genesis/login/login.h"
#include "../goblins.h"

object meditate;

void
create_room()
{
    object ob;
    ::create_room();

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_prop(ROOM_I_NO_MAGIC_ATTACK,"@@block_attack");
    add_prop(ROOM_I_NO_ATTACK,"@@block_attack");
    add_prop(ROOM_I_NO_STEAL,"@@block_attack");

    change_prop(ROOM_I_INSIDE,1);
    change_prop(ROOM_I_LIGHT,1);
    set_short("A small goblin chapel.");
    set_long(
        BSNN(
            "This room is dimly lit by hundreds of tiny candles. " +
            "There is a weird altar at the north end of the room. " +
            "The local shaman appears not to be in right now, and " +
            "no worshipers are present either.  Yet...you feel something, " +
            "a Presence...")  +
        BSNN("To the west, you see a door set in a smooth, flat wall. " +
             "To the northeast, you see a tunnel leading out. "));

    add_exit(GOBLIN_CAVERN_DIR + "tunnel2","northeast",0,0);
    add_exit(GOBLIN_CAVERN_DIR + "shaman_area","west",0,0);

    add_item(({"altar"}), BSN("The altar appears to be made " +
        "completely of bone.  Many bones in fact.  There appear to be many " +
        "different races represented here.  Two large human skulls top the " +
        "altar.  If a ghost should manage to come here and pray, " + 
        "Golzbog the Magnificent might resurrect him.  A living mortal " +
        "can meditate here, to reset his priorities."));

    add_item(({"wall"}), 
        "This wall has obviously been worked on by the goblins.\n");

    add_item(({"skull","skulls"}), 
        "The candles lit within them give the skulls an eerie life.\n");

    add_item(({"candle","candles"}),
        "These candles don't seem to wear out.\n ");

    ob = clone_object(GOBLIN_OBJ_DIR + "shaman_door");
    if (ob) {
        ob->move(this_object());
        ob->set_key(time());
    }

}

int
block_attack()
{
    write(BSN("You don't want to break the armed truce with these goblins."));
    return 1;
}


void
init()
{
    add_action("pray","pray");
    ::init();
}

void
all(string str)
{
    if (!this_player()->query_invis())
        say( ({BSN(METNAME + str), BSN(ART_NONMETNAME + str) }) );
}

pray()
{
  /*
   * First we see if the player has a ghost_player.c object.
   * If this is the fact, we'll make sure they've got a ghost
   * var set so the death mark will function, and then give
   * a new death mark to try to repeat the death sequence.
   */
    if (MASTER_OB(this_player()) == LOGIN_NEW_PLAYER)
    {
      /*
       * Player is a physical ghost. Make sure the ghost
       * var is 33 (GP_DEAD | GP_BODY) and send them to
       * the bodies room.
       */
        this_player()->set_ghost(GP_DEAD | GP_BODY);       
        write(BSN("You drift to the altar and pray.  After several " +
            "minutes of praying your dedication to evil, " +
            "you feel your wish is granted."));
        write("A voice reverberates through your soul:\n");
        write("\"GO FORTH AND SIN SOME MORE!\"\n");
        say(QCTNAME(this_player()) + " begins whispering a strange " +
            "prayer. The praying becomes more feverish, followed " +
            "by a flash of sickly green light!\n");
        this_player()->set_ghost(GP_DEAD | GP_BODY);       
        this_player()->move_living("M", "/d/Genesis/login/bodies", 1, 0);
        say(QCTNAME(this_player()) + " arrives in a flash of light.\n");
	return 1;
    }

  /*
   * Ok, the player isn't using a ghost_player.c object, but we
   * have to make sure it's not a normal player with a ghost
   * var set running around. That's an easy repair by just
   * removing the ghost variable.
   */
  if(this_player()->query_ghost()) {

    write(BSN("You drift to the altar and pray.  After several " +
          "minutes of praying your dedication to evil, " +
          "you feel your wish is granted."));
    write("A voice reverberates through your soul:\n");
    write("\"GO FORTH AND SIN SOME MORE!\"\n");

    if (!this_player()->query_invis())
      all(BSN("kneels at the altar and prays for several minutes. " +
          "As the prayer continues you see a body begin to " +
          "solidify where the ghost was.  The candles flicker momentarily."));
    this_player()->set_ghost(0);

  }
  else {
    write("You sense your prayers have been heard.\n");
    if (!this_player()->query_invis())
      all("kneels at the altar and mutters for a moment.");
  }

  return 1;
}

