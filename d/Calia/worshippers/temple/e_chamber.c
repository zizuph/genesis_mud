

 /* East Chamber of the Worshippers Temple
  * by Jaacar
  * July 22nd, 1996
  *
  * Modified on Feb 28, 2015 to remove ability to construct tools here.
  * One should use the new Elemental Temple - Petros
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER
#include <cmdparse.h>
#include <language.h>
#define WAND      WOR_OBJECTS+"wand"
#define CHALICE   WOR_OBJECTS+"chalice"
#define DAGGER    WOR_OBJECTS+"dagger"
#define PENTACLE  WOR_OBJECTS+"pentacle"
#define SCEPTRE   WOR_OBJECTS+"sceptre"

void next_step(int tool, int loop, object player);
int construct_id;
string comp_short;
object component;

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}


void
create_room()
{
    set_short("A small chamber");
    set_long("This small chamber has a wooden table with a "+
        "bench in front of it. On the table are several tools. "+
        "In the corner of the chamber you see a small forge, and a "+
        "pool filled with water. The adobe walls are covered by a "+
        "roof of grass and straw, which have become blackened near "+
        "the area surrounding the forge. The ground is a uniformly green, "+
        "evenly cut grass. The only exit is back to the west.\n");

    add_item(({"wooden table","table"}),"The table is not very "+
        "large, but roomy enough for one person to sit at to "+
        "use the tools that are on it.\n");

    add_item(({"wall","walls"}),"The adobe walls are made from "+
        "the same stones you have seen throughout the temple. "+
        "They are blackened near the area surrounding the forge.\n");
    add_item("bench","The bench is large enough for one person "+
        "to sit on, and made of the same wood as the table. It "+
        "appears to be well used.\n");

    add_item(({"tool","tools","several tools"}),"You see various "+
        "polished tools on the table. Among them you recognize "+
        "a fine chisel and a carving knife, but they look too dated " +
        "and brittle to use.\n");

    add_item(({"chisel","fine chisel"}),"The fine chisel seems to be made "+
        "from a weak metal and has a small wooden handle.\n");

    add_item(({"knife","carving knife"}),"The carving knife looks "+
        "very dull indeed. There is strange writing you do not "+
        "recognize on the hilt of the blade.\n");

    add_item(({"forge","small forge"}),"The forge is simply a small "+
        "stone pit with a burning hot flame in it. Atop of it you "+
        "see a small metal bowl which appears to have silver, gold, "+
        "copper, and platinum stains in it.\n");

    add_item(({"bowl","small bowl","metal bowl","small metal bowl"}),"It is "+
        "a small metal bowl. It is heavily stained with copper, "+
        "gold, silver, and platinum on the inside.\n");

    add_item(({"pool","water"}),"The pool is constructed from small "+
        "stones placed in a circular form. The water appears to be "+
        "clean and fresh.\n");

    add_item("grass","Every blade of grass here is the same shade "+
        "of green, and exactly the same height.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE+"entrance","west",0,1);
}

void
init()
{
    ::init();
    add_action("construct","construct");
    add_action("construct", "forge");
//    add_action("recover","recover");
//    add_action("carve","carve");
    add_action("drink","drink");
    add_action("enter","enter");
    add_action("destroy","destroy");
}

/*
 * function name: destroy
 * description  : Allows players to attempt to destroy a tool
 *                cancelling the power of it.
 * arguments    : string str - what to try destroy.
 * returns      : 0 - failure.
 *                1 - success.
 */
int
destroy(string str)
{
  /* Is the player a worshipper. */
    if (!is_worship(TP))
        return 0;

 
  /* Player tried to destroy the chalice */
    if (str == "chalice")
    {
        write_file(CARLOG, TP->query_name()+" uncarved their chalice on "+ctime(time())+".\n");
        write("You throw your Water Chalice into the forge and watch it melt "+
            "into nothingness.\n");
        tell_room(environment(TP),QCTNAME(TP)+" throws something into "+
            "the forge.\n",TP);

      /* Remove this element name to the player's SS_CARVED skill */
      if (TP->query_skill(SS_CARVED) &WATER_FLAG)
          TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) - WATER_FLAG));
      
      /* Adjust tax based on carving. */
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());

      /* De-activate the spells in the chalice. */
        present(WATER_OBJECT,TP)->remove_object();
        return 1;
    }

  /* Player tried to destroy the dagger */
    if (str == "dagger")
    {
        write_file(CARLOG, TP->query_name()+" uncarved their dagger on "+ctime(time())+".\n");
        write("You throw your Air Dagger into the forge and watch it melt "+
            "into nothingness.\n");
        tell_room(environment(TP),QCTNAME(TP)+" throws something into "+
            "the forge.\n",TP);

      /* Remove this element name to the player's SS_CARVED skill */
      if (TP->query_skill(SS_CARVED) &AIR_FLAG)
          TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) - AIR_FLAG));
      
      /* Adjust tax based on carving. */
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());

      /* De-activate the spells in the chalice. */
        present(AIR_OBJECT,TP)->remove_object();
        return 1;
    }

    /* Player tried to destroy the wand */
    if (str == "wand")
    {
        write_file(CARLOG, TP->query_name()+" uncarved their wand on "+ctime(time())+".\n");
        write("You throw your Fire Wand into the forge and watch it melt "+
            "into nothingness.\n");
        tell_room(environment(TP),QCTNAME(TP)+" throws something into "+
            "the forge.\n",TP);

      /* Remove this element name to the player's SS_CARVED skill */
      if (TP->query_skill(SS_CARVED) &FIRE_FLAG)
          TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) - FIRE_FLAG));
      
      /* Adjust tax based on carving. */
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());

      /* De-activate the spells in the chalice. */
        present(FIRE_OBJECT,TP)->remove_object();
        return 1;
    }
  
  /* Player tried to destroy the pentacle */
    if (str == "pentacle")
    {
        write_file(CARLOG, TP->query_name()+" uncarved their pentacle on "+ctime(time())+".\n");
        write("You throw your Earth Pentacle into the forge and watch it melt "+
            "into nothingness.\n");
        tell_room(environment(TP),QCTNAME(TP)+" throws something into "+
            "the forge.\n",TP);

      /* Remove this element name to the player's SS_CARVED skill */
      if (TP->query_skill(SS_CARVED) &EARTH_FLAG)
          TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) - EARTH_FLAG));
      
      /* Adjust tax based on carving. */
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());

      /* De-activate the spells in the chalice. */
        present(EARTH_OBJECT,TP)->remove_object();
        return 1;
    }

    /* Fail message. */
    write("Destroy what?\n");
    return 1;
}

/*
 * function name: carve
 * description  : Allows players to attempt to carve a word
 *                of power into an elemental tool.
 * arguments    : string str - what to try carving.
 * returns      : 0 - failure.
 *                1 - success.
 */
int
carve(string str)
{
    NF("What?\n");
    return 0;

  /* Is the player a worshipper. */
    if (!is_worship(TP))
        return 0;

  /* Is the player able to carve again? carve_count() returns */
  /* the number of times they have carved, carve_count(1) */
  /* returns the number of times they _can_ carve. */
    if (TP->carve_count() >= TP->carve_count(1))
    {
        write("You are not yet ready to carve upon your Elemental Tools.\n");
        return 1;
    }

  /* Is the player allowed to carve? I_CAN_CAST is the */
  /* name of an object that must be present. Indicates */
  /* council permission to carve. */
 /*
    if (!present(I_CAN_CAST,TP))
    {
        write("You have not yet been granted permission to carve.\n");
        return 1;
    }
 */

  /* Player tried to carve 'Meizon' */
    if (str == "Meizon")
    {
      /* Did they already try to carve meizon? */
        if (TP->query_skill(SS_CARVED) &WATER_FLAG)
        {
            write("You have already carved on your Water Chalice!\n");
            return 1;
        }

      /* Succeed carving. */
        write_file(CARLOG, TP->query_name()+" carved Meizon on "+ctime(time())+".\n");
        write("You take a fine chisel from the table and carve Meizon "+
            "into the Water Chalice, then return the chisel to the table.\n");
        tell_room(environment(TP),QCTNAME(TP)+" takes a tool from the table "+
            "and carves something into "+TP->query_possessive()+" chalice, "+
            "then returns the tool to the table.\n",TP);

      /* Add this element name to the player's SS_CARVED skill */
        TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) | WATER_FLAG));

      /* Adjust tax based on carving. */
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());

      /* Activate the spells in the chalice. */
        present(WATER_OBJECT,TP)->try_to_activate();
        return 1;
    }

  /* Remarks similar to those for Meizon, above. */
    if (str == "Egsousia")
    {
        if (TP->query_skill(SS_CARVED) &AIR_FLAG)
        {
            write("You have already carved on your Air Dagger!\n");
            return 1;
        }
        write_file(CARLOG,TP->query_name()+" carved Egsousia on "+ctime(time())+".\n");
        write("You take a fine chisel from the table and carve Egsousia "+
            "into the Air Dagger, then return the chisel to the table.\n");
        tell_room(environment(TP),QCTNAME(TP)+" takes a tool from the table "+
            "and carves something into "+TP->query_possessive()+" dagger, "+
            "then returns the tool to the table.\n",TP);
        TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) | AIR_FLAG));
        
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());
        present(AIR_OBJECT,TP)->try_to_activate();
        return 1;
    }

  /* Remarks similar to those for Meizon, above. */
    if (str == "Ergon")
    {
        if (TP->query_skill(SS_CARVED) &FIRE_FLAG)
        {
            write("You have already carved on your Fire Wand!\n");
            return 1;
        }
        write_file(CARLOG,TP->query_name()+" carved Ergon on "+ctime(time())+".\n");
        write("You take a fine chisel from the table and carve Ergon "+
            "into the Fire Wand, then return the chisel to the table.\n");
        tell_room(environment(TP),QCTNAME(TP)+" takes a tool from the table "+
            "and carves something into "+TP->query_possessive()+" wand, "+
            "then returns the tool to the table.\n",TP);
        TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) | FIRE_FLAG));
       
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());
        present(FIRE_OBJECT,TP)->try_to_activate();
        return 1;
    }

  /* Remarks similar to those for Meizon, above. */ 
    if (str == "Ischuroteros")
    {
        if (TP->query_skill(SS_CARVED) &EARTH_FLAG)
        {
            write("You have already carved on your Earth Pentacle!\n");
            return 1;
        }
        write_file(CARLOG,TP->query_name()+" carved Ischuroteros on "+ctime(time())+".\n");
        write("You take a fine chisel from the table and carve Ischuroteros "+
            "into the Earth Pentacle, then return the chisel to the table.\n");
        tell_room(environment(TP),QCTNAME(TP)+" takes a tool from the table "+
            "and carves something into "+TP->query_possessive()+" pentacle, "+
            "then returns the tool to the table.\n",TP);
        TP->set_skill(SS_CARVED, (TP->query_skill(SS_CARVED) | EARTH_FLAG));
        
        TP->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());
        present(EARTH_OBJECT,TP)->try_to_activate();
        return 1;
    }

  /* Fail message. */
    write("Carve what?\n");
    return 1;
}

int
recover(string str)
{
    NF("What?\n");
    return 0;
/*
    if (!is_worship(TP))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }
    if (str != "chalice" && str !="dagger" && str != "wand" && str !="pentacle" && str!="sceptre")
    {
        NF("What do you want to recover?\n");
        return 0;
    }
    if (str == "wand")
    {
        if (present("worshipper_wand", TP))
        {
            write("You already possess the Fire Wand!\n");
            return 1;
        }
        write_file(JOINLOG,TP->query_name()+" recovered wand on "+ctime(time())+".\n");
        clone_object(WAND)->move(TP,1);
        write("A Fire Wand materialized in your hands.\n");
        return 1;
    }
    if (str == "dagger")
    {
        if (present("worshipper_dagger", TP))
        {
            write("You already possess the Air Dagger!\n");
            return 1;
        }
        write_file(JOINLOG,TP->query_name()+" recovered dagger on "+ctime(time())+".\n");
        clone_object(DAGGER)->move(TP,1);
        write("An Air Dagger materialized in your hands.\n");
        return 1;
    }
    if (str == "chalice")
    {
        if (present("worshipper_chalice", TP))
        {
            write("You already possess the Water Chalice!\n");
            return 1;
        }
        write_file(JOINLOG,TP->query_name()+" recovered chalice on "+ctime(time())+".\n");
        clone_object(CHALICE)->move(TP,1);
        write("A Water Chalice materialized in your hands.\n");
        return 1;
    }
    if (str == "pentacle")
    {
        if (present("worshipper_pentacle", TP))
        {
            write("You already possess the Earth Pentacle!\n");
            return 1;
        }
        write_file(JOINLOG,TP->query_name()+" recovered pentacle on "+ctime(time())+".\n");
        clone_object(PENTACLE)->move(TP,1);
        write("An Earth Pentacle materialized in your hands.\n");
        return 1;
    }
    if (str == "sceptre")
    {
        if (present("worshipper_sceptre",TP))
        {
            write("You already possess the Sceptre!\n");
            return 1;
        }
        write_file(JOINLOG,TP->query_name()+" recovered sceptre on "+ctime(time())+".\n");
        clone_object(SCEPTRE)->move(TP,1);
        write("A Sceptre materialized in your hands.\n");
        return 1;
    }
    write("Recover what?\n");
    return 1;
*/
}

int
construct(string str)
{
    NF("You sense that the tools here are far too dated to construct anything of value. Perhaps you should seek somewhere else?\n");
    return 0;
    /*

    string comp_name;
    object *temp;

    if(is_worship(TP))
    {
        write("You don't need to construct anything! Try 'recover' if you "+
        "have lost one of your Tools.\n");
        return 1;
    }

    if (!str || !strlen(str))
    {
        NF("Forge what with what?\n");
        return 0;
    }

    if (sscanf(str, "%s with %s", str, comp_name) != 2)
    {
        NF("Construct what with what?\n");
        return 0;
    }

    if (str != "chalice" && str != "dagger" && str != "wand" && str != "pentacle")
    {
        NF("You cannot construct that here.\n");
        return 0;
    }

    if (!sizeof(temp = FIND_STR_IN_OBJECT(comp_name, TP)))
    {
        NF("Construct " + str + " with what?\n");
        return 0;
    }

    if (sizeof(temp) > 1)
    {
        NF("You can't construct " + LANG_ADDART(str) + " with more than " +
            "one thing, try again.\n");
        return 0;
    }

    if(get_alarm(construct_id))
    {
        write("Someone else is already using the tools. You will "+
            "have to try again in a few minutes.\n");
        return 1;
    }

    component = temp[0];

    if (str == "wand")
    {
        if (present("worshipper_wand",TP))
        {
            write("You already possess the Fire Wand!\n");
            return 1;
        }
        if ((!component->id("stick") &&
            !component->id("staff")) ||
            !present("copper coin",TP))
        {
            write("You do not have the necessary components to construct the Fire Wand.\n");
            return 1;
        }
        next_step(0, 1, TP);
        return 1;
    }
    if (str == "chalice")
    {
        if (present("worshipper_chalice", TP))
        {
            write("You already possess the Water Chalice!\n");
            return 1;
        }
        if ((!component->id("glass") &&
            !component->id("goblet") &&
            !component->id("chalice")) ||
            !present("gold coin", TP))
        {
            write("You do not have the necessary components to construct the Water Chalice.\n");
            return 1;
        }
        next_step(1,1,TP);
        return 1;
    }
    if (str == "dagger")
    {
        if (present("worshipper_dagger", TP))
        {
            write("You already possess the Air Dagger!\n");
            return 1;
        }
        if ((!component->id("dagger") &&
             !component->id("knife")) ||
             !present("silver coin",TP))
        {
            write("You do not have the necessary components to construct the Air Dagger.\n");
            return 1;
        }
        if (component->query_weapon_hits())
        {
            write("That " + component->short() + " is not pure!  " +
                "You must use a pure " + component->short() + ".\n");
            return 1;
        }

        next_step(2,1,TP);
        return 1;
    }
    if (str == "pentacle")
    {
        if (present("worshipper_pentacle", TP))
        {
            write("You already possess the Earth Pentacle!\n");
            return 1;
        }
        if ((!component->id("plate") &&
             !component->id("bowl")) ||
             !present("platinum coin", TP))
        {
            write("You do not have the necessary components to construct the Earth Pentacle.\n");
            return 1;
        }
        next_step(3,1,TP);
        return 1;
    }
    write("You cannot construct that here.\n");
    return 1;
    */
}

void
next_step(int tool, int loop, object player)
{
    object sac_coin;
    string coin_name;
    switch (loop)
    {
        case 1:
            coin_name = ({"copper","gold","silver","platinum"})[tool];
            sac_coin=present(coin_name + " coin", player);
            sac_coin->set_heap_size(sac_coin->num_heap() -1);
            tell_object(player, "You light a fire in the forge.\n");
            tell_room(this_object(), QCTNAME(player)+" lights "+
                "a fire in the small forge.\n",player);
            tell_object(player, "You place the " + coin_name +
                " coin into a metal bowl to melt.\n");
            tell_room(this_object(), QCTNAME(player)+" places "+
                "a "+coin_name+" coin into a metal bowl.\n",player);
            comp_short = component->short();
            component->add_prop(OBJ_M_NO_DROP, "You are in the middle of " +
                "working on the " + comp_short + ", you can't " +
                "put it down now.\n");
            break;
        case 2:
            tell_object(player, "You begin to prepare the "+comp_short+
                " using the tools from the table.\n");
            tell_room(this_object(), QCTNAME(player)+" begins "+
                "working on a "+comp_short+".\n",player);
            break;
        case 3:
            tell_object(player,"You finish your work on the "+
                comp_short+" and dip it into the forge to coat "+
                "it in metal.\n");
            tell_room(this_object(), QCTNAME(player)+" dips "+
                "the finished "+comp_short+" into the metal "+
                "bowl on the forge.\n",player);
            break;
        case 4:
            switch (tool)
            {
                case 0:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Pyros' and '"+
                        capitalize(player->query_real_name())+
                        "' onto the "+
                        "shaft.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                    "into a wand.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Fire Wand.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged wand.\n",player);
                    component->remove_object();
                    clone_object(WAND)->move(player,1);
                    write_file(CONLOG,player->query_name()+" constructed wand on "+ctime(time())+".\n");
                    break;
                case 1:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Diabrecho' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "rim.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "into a chalice.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Water Chalice.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged chalice.\n",player);
                    component->remove_object();
                    clone_object(CHALICE)->move(player,1);
                    write_file(CONLOG,player->query_name()+" constructed chalice on "+ctime(time())+".\n");
                    break;
                case 2:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Aeria' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "hilt.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "onto a dagger.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Air Dagger.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged dagger.\n",player);
                    component->remove_object();
                    clone_object(DAGGER)->move(player,1);
                    write_file(CONLOG,player->query_name()+" constructed dagger on "+ctime(time())+".\n");
                    break;
                case 3:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Gu' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "outer rim.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "into a pentacle.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Earth Pentacle.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged pentacle.\n",player);
                    component->remove_object();
                    clone_object(PENTACLE)->move(player,1);
                    write_file(CONLOG,player->query_name()+" constructed pentacle on "+ctime(time())+".\n");
                    break;
            }
            break;
    }
    if (loop == 4)
        return;

    loop++;
    construct_id=set_alarm(5.0, 0.0, &next_step(tool, loop, player));
    return;
}

int
drink()
{
    write("You think about drinking the water, but then suddenly "+
        "decide against it. Very strange.\n");
    return 1;
}

int
enter()
{
    write("You would not fit inside!\n");
    return 1;
}
