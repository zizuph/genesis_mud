/*
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch, Nov 2020
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/camp10"

#define ELFCAMP "/d/Krynn/qualinesti/elf_camp/"
#define FOREST "/d/Krynn/qualinesti/forest/"

#define ELFPATH "/d/Krynn/guilds/elven_archers/fortnexus_elf"

object fortnexus_elf;

void
reset_krynn_room()
{
    if(!objectp(fortnexus_elf))
    {
        fortnexus_elf = clone_object(ELFPATH);
        fortnexus_elf->move(TO);
    }
}

void
create_krynn_room()
{

    set_short("the thrumming nexus of a treetop fortress");

    set_long(gBlurbPfx + 
             " This room lies at the heart of the fortress, the thrumming nexus from where the "+
             "entire forest below is monitored. The silken strands that bind "+
             FORTNAME + " together, also extend throughout the forest in a web that transmits every vibration, "+
             "every footfall at its roots to this very place. "+
             "This vast room is filled with an immense loom of strands, held precisely in place by "+
             "arrow shafts protruding from branches on the floor, walls and ceiling. The great loom is "+
             "tended and tuned by a diminutive elf, ever rushing about and making fine adjustments to "+
             "tensions and angles.  In opposing corners of the room stand two gigantic bow-harps, "+
             "one of ebon and one of white oak. "+
             gBlurbSfx +
             " Many openings lead in all directions to other parts of the fortress.\n");

    add_item(({"bow-harp","bow-harps","harp","harps"}),
              "There are two bow-harps, one of ebon and one of oak.\n");

    add_item(({"ebon bow-harp","ebon harp"}),
              "On the left stands a gigantic ebon bow-harp, "+
              "by which Elven Archers can <lament> the loss of those of their "+
              "kin who have fallen from the light -- a mournful sound "+
              "to be heard throughout all the Realms.\n");

    add_item(({"oak bow-harp","oak harp"}),
              "On the right stands a gigantic bow-harp of white oak, "+
              "by which Elven Archers can <broadcast> their messages of great import "+
              "to alert all their kin throughout all the Realms.\n");

    gViewFallDest = VIEWDEST;

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("The network of silken strands stretches and shifts with the gentle movement of the treetops.\n");

    INSIDE
    
    add_exit(GUILDROOMS + "fort_reservoir", "north", 0);
    add_exit(GUILDROOMS + "fort_board", "west", 0);
    add_exit(GUILDROOMS + "fort_rack1", "south", 0);
    add_exit(GUILDROOMS + "fort_rack2", "southwest", elite_check);
    add_exit(GUILDROOMS + "fort_dorm", "southeast", 0);
    add_exit(GUILDROOMS + "fort_postoffice", "northeast", 0);

    reset_krynn_room();
}

public mixed *
good_archer_list()
{
    int nu, iu;
    string *str;
    string *garcher;
    object *user;

    // does not return linkdead players
    user = users();
    nu = sizeof(user);

    garcher = ({ });
    str = allocate(1);

    for (iu=0;iu<nu;iu++)
    {
       if (!objectp(user[iu])) continue;

       str[0] = user[iu]->query_real_name();

       if ( !objectp(find_player(str[0])) ) continue;

       if ( (user[iu]->query_guild_name_occ() == "Ansalon Elvish Archers") ||
            (user[iu]->query_guild_name_lay() == "Ansalon Elvish Archers") )
       {
           if ( user[iu]->query_alignment() > -100 )
           {
               garcher += str[0..0];

           }
       }

    }

    return garcher;
}


public mixed *
evil_archer_list()
{
    int nu, iu;
    string *name, *str;
    object *user;

    // does not return linkdead players
    user = users();
    nu = sizeof(user);

    name = ({ });
    str = allocate(1);

    for (iu=0;iu<nu;iu++)
    {
       if (!objectp(user[iu])) continue;

       str[0] = user[iu]->query_real_name();

       if ( !objectp(find_player(str[0])) ) continue;

       if ( (user[iu]->query_guild_name_occ() == "Ansalon Elvish Archers") ||
            (user[iu]->query_guild_name_lay() == "Ansalon Elvish Archers") )
       {
           if ( user[iu]->query_alignment() < -100 )
           {
               name += str[0..0];
           }
       }

    }

    return name;
}

int
do_broadcast(string sender, string message_txt)
{
    string *garcher;
    object archer;
    int n, i;

    garcher = good_archer_list();

    n = sizeof(garcher);

    for (i=0;i<n;i++) 
    {

        archer = find_player(garcher[i]);
        if (!archer) return 0; 

        archer->catch_msg(
      "A thrumming in the air and in your chest bears a broadcast message "
      + "from " + sender + " of " + FORTNAME + " to all good "
      +"Elven Archers of Ansalon:\n"
      + message_txt + "\n");
    }

    return 1;
}

int
broadcast_good(string message_txt)
{
    string report;
    string sender;
    object *garcher;
    int n, i;

    if(!strlen(message_txt))
    {
        write("Broadcast what?\n");
        return 0;
    }
 
    sender = QNAME(this_player());

    write("You send an urgent signal out on the great oak bow-harp.\n");
    say(sender + " sends an urgent signal on the great oak bow-harp.\n");

    set_alarm(2.0,0.0,&do_broadcast(sender,message_txt));

    return 1;
}

int
do_lament( string lamenter )
{

    string *earcher;
    object archer;
    string treesps = "oak beech birch chestnut "+
                     "aspen elm maple linden ash "+
                     "cherry spruce cedar pine "+
                     "walnut gum sycamore willow";
    string *treesp;
    int n, i, nrnd, j;

    earcher = evil_archer_list();

    n = sizeof(earcher);

    treesp = explode(treesps, " ");
    nrnd = sizeof(treesp) - 1;

    for (i=0;i<n;i++) 
    {
        archer = find_player(earcher[i]);
        if (!archer) return 0; 

        j = random(nrnd);

        archer->catch_msg(
          "Your fall from grace is lamented by " + lamenter
           + " of " + FORTNAME + ". The elder " + treesp[j] + " trees "+
           "of Qualinesti add their voices to the chorus.\n");

        write("You are joined in a lament for lost archers by the elder stands of "
               + treesp[j] + "trees throughout the forest.\n");

        say(lamenter + " is joined in a lament for lost archers by the elder stands of "
               + treesp[j] + "trees throughout the forest.\n");

    }

    return 1;
}

int
lament_evil()
{
    string lamenter;

    lamenter = QNAME(this_player());

    write("You solemnly strum a lament on the great ebon bow-harp.\n");
    say(lamenter + " solemnly strums a lament on the great ebon bow-harp.\n");

    set_alarm(2.0,0.0,&do_lament(lamenter));

    return 1;
}

void
init()
{
    ::init();
    add_action("broadcast_good", "broadcast");
    add_action("lament_evil", "lament");
}

