#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit CAVERNS_BASE;
inherit "/lib/commands";

object altar;

void
reset_tharkadan_room()
{
    if(!objectp(altar))
    {
        altar = clone_object(TOBJ + "theiwar_altar");
        altar->move(TO, 1);
    }

}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "upper_mines10","south",0);

    add_prop(ROOM_S_DARK_LONG, "Darkness surrounds you.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, -8);

    add_item(({"large chamber","chamber","room","dark chamber"}),
        "This large chamber seems to have been carved out of a single " +
        "vein of black onyx! It is clearly a place of reverence to the " +
        "dark dwarves.\n");
    add_item(({"floor"}),
        "The floor reminds you of a black lens, concaving down to meet " +
        "at the center of the chamber where squats an altar to a dark " +
        "god.\n");
    add_item(({"smooth black onyx","black onyx","onyx"}),
        "The entire room seems to be carved out of a single vein of " +
        "black onyx!\n");

    reset_tharkadan_room();
}

string
short_descr()
{
    return "an unnaturally dark chamber of black onyx";
}

string
long_descr()
{
    return "You stand within a large chamber carved out of smooth black " +
        "onyx, its floor concaving down to the center of the room where " +
        "squats the only object to be found here, a great spherical " +
        "altar that seems to exude darkness and devour light. The only " +
        "exit from this chamber is to your south.\n";
}

public void
init()
{
    ::init(); 
    add_action("offer_sacrifice", "sacrifice");
    add_action("offer_sacrifice", "offer"); 
}

public int
offer_sacrifice(string str)
{
    object * oblist;
    object player = this_player();
    object vial, pot;
    int in;

    
    if (!str)
    {
        notify_fail("Offer what to the altar?\n");
        return 0;
    }

    oblist = parse_this(str, "%o [to] [the] [altar]");
    if (!sizeof(oblist))
    {
        return 0;
    }

    if (!oblist[0]->id("_WoHS_black_sacrificial_disk") &&
        !oblist[0]->id("_WoHS_multi_sacrificial_disk") &&
        !oblist[0]->id("_WoHS_sacrificial_giant_braid") &&
        !oblist[0]->id("_WoHS_sacrificial_black_orb"))
    {
        write("You offer the " +oblist[0]->query_short()+ " as a " +
            "sacrifice, however nothing happens.\n"); 
        say(QCTNAME(TP)+ " offers the " +oblist[0]->query_short()+ " as " +
            "a sacrifice, however nothing happens.\n");
        return 1;
    }

    player->catch_tell("You kneel beside the spherical black altar and " +
        "offer the " +oblist[0]->short()+ " as a sacrifice. The altar " +
        "seems to pulse with approval, and the "+oblist[0]->short()+ 
        " vanishes!\n");
    tell_room(environment(player), QCTNAME(player)+ " kneels beside the " +
        "spherical black altar and offers a " +oblist[0]->short()+ 
        " as a sacrifice. The altar seems to pulse with dark approval, " +
        "and the "+oblist[0]->short()+ " vanishes!\n", ({ player }), 
        player);

    setuid();
    seteuid(getuid());

    if(TP->query_guild_name_occ() != "Wizards of High Sorcery" &&
       TP->query_guild_name_occ() != "School of High Magic")
    {
        write("You hear a rasping voice in your mind say with dark " +
            "amusement: My dark reward for your sacrifice is beyond " +
            "your ability to use, Walk the path of the magi under the " +
            "guidance of the three moons of magic... only then will " +
            "you be worthy of my reward!\n");

        oblist[0]->remove_object();

        return 1;
    }

    // Black orb provides the cantrip wind gust
    if (oblist[0]->id("_WoHS_sacrificial_black_orb"))
    {
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"suacotrekis"))
        {
            write("You hear a rasping voice in your mind say with dark " +
                "displeasure:  You have already received my reward for " +
                "such a sacrifice, Wizard. You need to impress me with " +
                "something else that I desire!\n");

            oblist[0]->remove_object();
      
            return 1;
        }

        write("\nYou hear a rasping voice in your mind say with dark " +
            "approval: You return to me a piece of my celestial body, " +
            "a piece of the blackest night! I grant you this boon, " +
            "mortal... a spell that will better allow you to control " +
            "the darkness you evoke, but not the darkness in your " +
            "heart.\n");
        WOHS_MANAGER->scribe_spell_to_spellbook(player, "suacotrekis");
        write("\n\nThe cantrip suacotrekis has been scribed into your " +
            "spellbook!\n\n");

        oblist[0]->remove_object();

        return 1;
    }

    // Giant braid provides the advanced spell eruption
    if (oblist[0]->id("_WoHS_sacrificial_giant_braid"))
    {
        if(TP->query_guild_name_occ() == "School of High Magic")
        {
            write("You hear a rasping voice in your mind say with " +
                "dark amusement: My dark reward for your sacrifice is " +
                "beyond your ability at the moment, Aspirant. Pass the " +
                "Test of High Sorcery and you may be ready for such " +
                "a spell!\n");

            oblist[0]->remove_object();

            return 1;
        }     
        if((TP->query_advanced_spells_max() < 1)) 
        {
            write("You hear a rasping voice in your mind say with dark " +
                "amusement: My dark reward for your sacrifice is " +
                "beyond your ability at the moment, Wizard. Achieve the " +
                "ability to cast advanced spells and you may be ready " +
                "for my reward!\n");

            oblist[0]->remove_object();

            return 1;
         }
         if(WOHS_MANAGER->query_scribed_spell(this_player(),"virednith"))
         {
              write("You hear a rasping voice in your mind say with " +
                  "dark displeasure: You have already received my " +
                  "reward for such a sacrifice, Wizard. You need to " +
                  "impress me with something else that I desire!\n");

              oblist[0]->remove_object();
      
              return 1;
         }

         write("\nYou hear a rasping voice in your mind say with dark " +
             "glee: Stone giants are the bones of the earth from the " +
             "Age of Starbirth! And the spirit of fire! And so I grant " +
             "you the ability to " +
             "summon the elements to do your violent bidding!\n");
         WOHS_MANAGER->scribe_spell_to_spellbook(player, "virednith");
         write("\n\nThe advanced spell virednith has been scribed " +
             "into your spellbook!\n\n");

         oblist[0]->remove_object();

         return 1;
    }

    // Black disk provides the advanced spell meteor storm
    if (oblist[0]->id("_WoHS_black_sacrificial_disk"))
    {
        if(TP->query_guild_name_occ() == "School of High Magic")
        {
            write("You hear a rasping voice in your mind say with " +
                "dark amusement: My dark reward for your sacrifice is " +
                "beyond your ability at the moment, Aspirant. Pass the " +
                "Test of High Sorcery and you may be ready for such " +
                "a spell!\n");

            oblist[0]->remove_object();

            return 1;
        }     
        if((TP->query_advanced_spells_max() < 1)) 
        {
            write("You hear a rasping voice in your mind say with " +
                "dark amusement: My dark reward for your sacrifice is " +
                "beyond your ability at the moment, Wizard. Achieve the " +
                "ability to cast advanced spells and you may be ready " +
                "for my reward!\n");

            oblist[0]->remove_object();

            return 1;
        }
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"tonashkepesk"))
        {
            write("You hear a rasping voice in your mind say with " +
                "dark displeasure: You have already received my reward " +
                "for such a sacrifice, Wizard. You need to impress me " +
                "with something else that I desire!\n");

            oblist[0]->remove_object();
      
            return 1;
        }

        write("\nYou hear a rasping voice in your mind say with dark " +
            "pleasure: I grant you a fitting reward for your sacrifice " +
            "of such an item! From the dark skies above I watch the " +
            "world, and this summoning too comes from the heavens!\n");
        WOHS_MANAGER->scribe_spell_to_spellbook(player, "tonashkepesk");
        write("\n\nThe advanced spell tonashkepesk has been scribed " +
            "into your spellbook!\n\n");

        oblist[0]->remove_object();

        return 1;
     }


    // Multi-hued disk provides the advanced spell protection from magic
    if (oblist[0]->id("_WoHS_multi_sacrificial_disk"))
    {
        if(TP->query_guild_name_occ() == "School of High Magic")
        {
            write("You hear a rasping voice in your mind say with dark " +
                "amusement: My dark reward for your sacrifice is beyond " +
                "your ability at the moment, Aspirant. Pass the Test of " +
                "High Sorcery and you may be ready for such a spell!\n");

            oblist[0]->remove_object();

            return 1;
        }     
        if((TP->query_advanced_spells_max() < 1)) 
        {
            write("You hear a rasping voice in your mind say with " +
                "dark amusement: My dark reward for your sacrifice is " +
                "beyond your ability at the moment, Wizard. Achieve the " +
                "ability to cast advanced spells and you may be ready " +
                "for my reward!\n");

            oblist[0]->remove_object();

            return 1;
        }
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"trotharcanis"))
        {
            write("You hear a rasping voice in your mind say with " +
                "dark displeasure: You have already received my reward " +
                "for such a sacrifice, Wizard. You need to impress me " +
                "with something else that I desire!\n");

            oblist[0]->remove_object();
      
            return 1;
        }

        write("\nYou hear an emotionless rasping voice in your mind: " +
            "When the three moons of magic align in the sky it is a " +
            "time of great power for Wizards of High Sorcery, an event " +
            "known as the Night of the Eye. While your powers will be " +
            "enhanced, so too will the powers of other wizards! And " +
            "so I grant you this dark gift, to protect you from the " +
            "schemes of other wizards!\n");
        WOHS_MANAGER->scribe_spell_to_spellbook(player, "trotharcanis");
        write("\n\nThe advanced spell trotharcanis has been scribed " +
            "into your spellbook!\n\n");

        oblist[0]->remove_object();

        return 1;
    }

    oblist[0]->remove_object();
        
    return 1;
}
