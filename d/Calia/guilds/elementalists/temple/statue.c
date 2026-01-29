/*
 * Statue Room in the Inner Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM_BASE;

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <math.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines

// Prototypes
int ceremony_status = 0;
int candles = 0;
string *cleric_elders = ({ });
string *worshippers_council = ({ });

public void
create_temple_room()
{
    set_short("Elemental Temple Statue Room");
    set_long("This large chamber is part of the third and innermost circle "
             + "of the Elemental Temple. The circular wall surrounding this "
             + "tall chamber is made from grey stone and pure crystalline. "
             + "Looking up, you see that it reaches high up and forms a "
             + "vast dome. Just underneath the domed area you can see small "
             + "windows that let in a small amount of light. On the northern "
             + "side of this room, you see the shrouded crystalline walls "
             + "that make up the inner sanctum of the Temple. In the center, "
             + "a dais occupies much of the room. Upon the dais several "
             + "statues are erected here. On a small table against the northern "
             + "wall you see some white candles.\n\n");
    add_item(({"candle","candles","white candle","white candles"}),
        "@@check_candles@@");
        
    add_item(({"table","small table","small maple table","maple table"}),
        "The small table is made from maple, and inlaid with quartz and "+
        "marble. Several white candles rest on it, along "+
        "with a brazier with smoldering coals. A cup full of long, dry "+
        "bits of straw is also there, for use when lighting candles.\n");
    
    add_item("stand", "The stand is old, and covered in hardened wax in "+
      "many places. Candles are arranged in rows of intertwining circles, "+
      "allowing their soft light to fill the room.\n");
      
    add_item(({"statue","statues","several statues","many statues"}),"@@check_elders@@");
    
    add_item( ({ "statue of jardeth" }), "The statue of Jardeth depicts "
        + "an ancient sparkling-cloaked male elf who appears to be holding an "
        + "herb in his hands and sniffing it carefully.\n");
    add_item( ({ "statue of tahla" }), "The statue of Tahla depicts a "
        + "captivating crystalline-cloaked female elf who is examining "
        + "some clerical scrolls.\n");
    add_item( ({ "statue of arial" }), "The statue of Arial is of a "
        + "beautiful white-cloaked female elf who holds a gem up to her eye "
        + "and is carefully examining it.\n");
    add_item( ({ "statue of tiashe" }), "The statue of Tiashe depicts a "
        + "beautiful blue-cloaked female elf smiling warmly. She reaches "
        + "forward in benevolence as if to share the bread in her hands.\n");
    add_item( ({ "statue of sehis" }), "The statue of Sehis depicts a "
        + "beautiful silver-cloaked female elf smiling warmly. She is looking "
        + "at you in a very welcoming way.\n");
          
    try_item( ({ "wall", "walls" }),
              "Which wall? The circular wall or the shrouded crystalline wall?\n");

    try_item( ({ "circular wall" }),
              "The circular wall of the Inner Circle is hewn from a grey rock "
              + "material, with crystalline veins tightening the structure and "
              + "covering the surface of the rock wall. The surface is very "
              + "smooth to the touch and you can see your own partial reflection "
              + "upon the grey surface. The wall continues all the way up to "
              + "form a massive dome.\n");
    try_item( ({ "shrouded wall", "shrouded crystalline wall", "crystalline wall" }),
              "The shrouded crystalline wall on the northern part of the statue room "
              + "doesn't have the typical clear radiance of crystalline. Instead, the "
              + "material is shrouded, making it impossible to view the inner sanctum "
              + "of the Temple.\n");

    try_item( ({ "dome", "massive dome", "ceiling" }),
              "A dome of massive proportions looms over you, covering the entire Inner "
              + "Circle, which includes the inner sanctum. The dome consists of countless "
              + "glass and crystalline pieces in every possible color of the rainbow. "
              + "When light shines through from above, the entire Inner Circle is bathed "
              + "in a formidable mosaic that coalesces into an eternal dance of colours.\n");

    try_item( ({ "windows", "small windows", "window", "small window", "mosaic" }),
              "The small windows sit beneath the beginning of the massive dome. A small "
              + "amount of light streams through them, hitting the dome and creating "
              + "a beautiful mosaic that coalesces into an eternal dance of colours.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "green crystalline webbing", "coating", "crystalline coating" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls.\n");

    try_item( ({ "inner sanctum", "sanctum" }),
              "The inner sanctum of the Elemental Temple is the central location and "
              + "most sacred of places in this Temple. The base of the circular room "
              + "is made from a shadowy shrouded crystalline that prevents an "
              + "observer from seeing the activities inside.\n");

    try_item( ({ "dais" }),
              "Before you a slendar dais occupies much of the room, providing a "
              + "raised platform for the many statues that sit on top of it. "
              + "The dais is made from black obsidian, adding stout reverence to "
              + "the gentle luminescence of this room. A small copper plaque has "
              + "been placed in a corner of the dais.\n");

    try_item( ({ "small copper plaque", "plaque", "copper plaque", "small plaque", "corner" }),
              "The plaque reads: \"Reverence\". Somehow, you just know that the statues "
              + "commemorate the most revered servants of the Elementals.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "inner5", "west");
    add_exit(ELEMENTALIST_TEMPLE + "inner6", "east"); 
    add_exit(ELEMENTALIST_TEMPLE + "private_chapel", "south","@@check_ceremony@@"); 
}

void
set_ceremony(int i)
{
    ceremony_status = i;
}

int
check_ceremony()
{
    if (ceremony_status)
    {
        if (!IS_MEMBER(TP))
        {
            write("The chapel is closed at the moment as there is a "+
                "ceremony taking place. Please come back later.\n");
            return 1;
        }
        else
        {
            write("\n\nThere is a ceremony taking place right now. You are "+
                "permitted to enter but please be quiet.\n\n");
            return 0;
        }
    }

    return 0;
}

int
do_touch(string str)
{
	int taskone, tasktwo, taskthree, taskfour;
	
	if (!str)
        return 0;
	
	if (parse_command(str, ({}),"[the] [small] [copper] 'plaque'"))
    {
		// If they aren't a Seeker, nothing will happen.
		if (!(GUILD_MANAGER->query_is_seeker(TP)))
		{
			write("Nothing happens.\n");
	        return 1;
	    }
	    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
	    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
	    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
	    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
	    
	    // If they haven't been assigned task one, nothing will happen.
	    if (!taskone)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task two, nothing will happen.
	    if (!tasktwo)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task three, nothing will happen.
	    if (!taskthree)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task four, nothing will happen.
	    if (!taskfour)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    /// If they haven't already completed the pool part of task four, nothing will happen.
	    if (taskfour < 5)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they've already completed task four, nothing will happen.
	    if (taskfour == 6)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // They are indeed a Seeker and have been assigned task four and have not
	    // yet completed it.
	    GUILD_MANAGER->set_can_do_wor_task_four(TP, 6);
	    write("You hear a voice echo in your mind saying: We have served the Elementals. "+
	        "We have served and worshipped with Faith, we took the vow of Family, "+
	        "and we will remember always the Trust and Secrecy bestowed upon us. "+
	        "Remember that 'Secrecy' is paramount to who we were, who we are, and "+
	        "who we must become.\nYou somehow feel the answer to your search is "+
	        "'Secrecy'.\n");
	    return 1; 
	} 
	return 0;
}

string
check_candles()
{
    string str;
    str = "The small, round candles are of varying height are displayed "+
          "in a large metal stand. ";
    if (candles == 0)
        str += "There are no candles lit.\n";

    else if (candles == 1)
        str += "There is only one candle lit.\n";

    else
        str += "There are "+LANG_NUM2WORD(candles)+" candles lit.\n";

    return str;
}


int
do_light(string str)
{
    string for_who;
    object who;

    if (!str)
    {
        NF("Light what? A candle for whom?\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[a] 'candle' [for] %s", for_who))
    {
        NF("Light what? A candle for whom?\n");
        return 0;
    }

    who = find_player(lower_case(for_who));

    if (!who)
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        return 1;
    }

    if (IS_MEMBER(who))
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        tell_object(who,"You feel that "+capitalize(TP->query_real_name())+
            " has lit a candle in your honour and is praying to Psuchae "+
            "for the well being of your soul.\n");
        return 1; 
    }

    if (who->query_wiz_level())
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        tell_object(who,"You feel that "+capitalize(TP->query_real_name())+
            " cares enough for you to "+
            "light a candle in your honour in the mortal realm.\n");
        return 1;
    }

    write("You light a small white candle and pray for "+
        capitalize(for_who)+".\n");
    say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
        "before it.\n");
    tell_object(who,"You feel someone has prayed for you somewhere "+
        "in the realms, to ask Psuchae to help watch over your soul.\n");
    candles += 1;
    return 1;
}

int
do_extinguish(string str)
{
    if (!str)
        return 0;

    write("You do not dare extinguish any of the holy candles.\n");
    say(QCTNAME(TP)+" thinks about extinguishing the candles, but "+
        "decides against it at the last moment.\n");
    return 1;
}

string
check_num_elders()
{
    string str;
    int i;

    i = sizeof(cleric_elders);

    switch(i)
    {
        case 0:
            str = "is one statue";
            break;
        case 1..3:
            str = "are a few statues";
            break;
        case 4..6:
            str = "are several statues";
            break;
        default:
            str = "are many statues";
            break;
    }
    return str;
}

private int
query_is_cleric_npc(string name)
{
    switch (lower_case(name))
    {
    case "jardeth":
    case "arial":
    case "tiashe":
    case "tahla":
    case "sehis":
        return 1;
    }
    
    return 0;
}

private int
cleanup_elders()
{
    string * cleric_npcs, * cleric_players;
    string nonmetname, desc;
    // Clean up juniors
    cleric_elders = filter(cleric_elders, &not() @ &wildmatch("*jr"));
    cleric_npcs = filter(cleric_elders, query_is_cleric_npc);
    cleric_players = cleric_elders - cleric_npcs;
    foreach (string elder : cleric_players)
    {
        if (!SECURITY->exist_player(elder))
        {
            cleric_elders -= ({ elder });
            continue;
        }
        
        object player_obj;
        int offline = 0;
        if (!objectp(player_obj = find_living(elder)))
        {
            if (!objectp(player_obj = SECURITY->finger_player(elder)))
            {
                // Should never occur.
                send_debug_message("cleric_statue", "Was not able to find "
                    + elder + " anywhere.");
                continue;
            }            
            offline = 1;
        }
        // We should have a valid player_obj at this point
        send_debug_message("cleric_statue", "Elder " + elder + " is a "
            + player_obj->query_nonmet_name() + ".");
        nonmetname = player_obj->query_nonmet_name();
        remove_item("statue of " + elder);
        switch (NAME_TO_RANDOM(elder, 0, 5))
        {
        case 0:
            desc = "standing piously in prayer.\n";
            break;
        
        case 1:
            desc = "deep in thought.\n";
            break;
        
        case 2:
            desc = "gazing heavenward.\n";
            break;
        
        case 3:
            desc = "with blurred shadowy features.\n";
            break;
        
        case 4:
        default:
            desc = "with arms extended grasping a mandala.\n";
            break;
        }
        
        add_item( ({ "statue of " + elder }), "The statue of "
            + capitalize(elder) + " has been constructed meticulously "
            + "and shows a " + nonmetname + " " + desc);
        if (offline)
        {
            player_obj->remove_object();
        }
    }
}

private int
cleanup_worshippers()
{
    string * worshipper_players;
    string nonmetname, desc;
    // Clean up juniors
    worshippers_council = filter(worshippers_council, &not() @ &wildmatch("*jr"));
    worshipper_players = worshippers_council;
    foreach (string ewcouncil : worshipper_players)
    {
        if (!SECURITY->exist_player(ewcouncil))
        {
            worshippers_council -= ({ ewcouncil });
            continue;
        }
        
        object player_obj;
        int offline = 0;
        if (!objectp(player_obj = find_living(ewcouncil)))
        {
            if (!objectp(player_obj = SECURITY->finger_player(ewcouncil)))
            {
                // Should never occur.
                send_debug_message("cleric_statue", "Was not able to find "
                    + ewcouncil + " anywhere.");
                continue;
            }            
            offline = 1;
        }
        // We should have a valid player_obj at this point
        send_debug_message("cleric_statue", "EWCouncil " + ewcouncil + " is a "
            + player_obj->query_nonmet_name() + ".");
        nonmetname = player_obj->query_nonmet_name();
        remove_item("statue of " + ewcouncil);
        switch (NAME_TO_RANDOM(ewcouncil, 0, 2))
        {
        case 0:
            desc = "standing piously in prayer.\n";
            break;
        
        case 1:
            desc = "deep in thought.\n";
            break;
        
        default:
            desc = "gazing heavenward.\n";
            break;
                
        }
        
        add_item( ({ "statue of " + ewcouncil }), "The statue of "
            + capitalize(ewcouncil) + " has been constructed meticulously "
            + "and shows a " + nonmetname + " " + desc);
        if (offline)
        {
            player_obj->remove_object();
        }
    }
}
string
check_elders()
{
    string str;
    int i, j, k;

    setuid();
    seteuid(getuid());
    cleric_elders = GUILD_MANAGER->query_all_elders();
    cleanup_elders();
//    worshippers_council = GUILD_MANAGER->query_ew_council();
//    cleanup_worshippers();
    
    i = sizeof(cleric_elders);

    if (i == 0)
        str = "There are five statues: Arial, Jardeth, Sehis, Tahla, Tiashe.\n";
    
    else if (i == 1)
        str = "There are six statues: Arial, Jardeth, Sehis, Tahla, Tiashe, "+
            capitalize(cleric_elders[0]) + ".\n";
    
    else
    {
        j = i + 5;
        str = "There are "+LANG_NUM2WORD(j)+" statues: Arial, Jardeth, Sehis, "+
            "Tahla, Tiashe, ";
        str += (COMPOSITE_WORDS(map(cleric_elders, capitalize)) + ".\n");
    }
    
//    k = sizeof(worshippers_council);
    
//    if (k == 0)
//        str += "There are no worshipper statues.\n";
        
//    else if (k == 1)
//        str += "There is one worshipper statues: "+
//            capitalize(worshippers_council[0]) + ".\n";
    
//    else
//    {
//        str += "There are "+LANG_NUM2WORD(k)+" worshipper statues: ";
//        str += (COMPOSITE_WORDS(map(worshippers_council, capitalize)) + ".\n");
//    }
    
    return str;
}

public void
init()
{
    ::init();
    add_action(do_touch,"touch");
    add_action(do_light,"light");
    add_action(do_extinguish,"extinguish");
    add_action(do_extinguish,"unlight");
}
