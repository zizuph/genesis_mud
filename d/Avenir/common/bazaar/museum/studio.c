/* Studio where players can have a statue of themselves
 * made.
 *   Cirion 040296
 */
inherit "/d/Avenir/common/bazaar/museum/std_museum";
inherit "/lib/trade";
#include "museum.h"
#include "/d/Avenir/smis/sys/statserv.h"

#define WEAR_STR ({ "is depicted to be wearing", "wears", "is shown as wearing" })

#define MRND(x)   x[random(sizeof(x))]

/* Prototypes */
int      remove_statue(string name);
int      remove(string str);
int      do_pay(string str);
string   generate_desc(object who);
string   material(object who);
string   access_block();
static object   sculptor;

#define NUM_STATUE_ROOMS 15

/* Format for statues : name, desc */
public string  *statue1 = ({ }),
               *statue2 = ({ }),
               *statue3 = ({ }),
               *statue4 = ({ }),
               *statue5 = ({ }),
               *statue6 = ({ }),
               *statue7 = ({ }),
               *statue8 = ({ }),
               *statue9 = ({ }),
               *statue10 = ({ }),
               *statue11 = ({ }),
               *statue12 = ({ }),
               *statue13 = ({ }),
               *statue14 = ({ }),
               *statue15 = ({ });

void create_room()
{
    set_short("studio");
    set_long("This is a large room that feels small, as it is almost "
        +"completely filled with enormous blocks of "
        +"stone. Tools and stone chippings lay scattered "
        +"all about the floor, and a large stepladder leans "
        +"against the western wall. This is the studio where "
		+"the sculptor works on the commissions he receives "
		+"from patrons such as yourself. There is a sign "
        +"chiseled into the stone by the entrance.\n");

    add_item(({"stone","block","blocks", "slab","slabs"}),"They are "
        +"massive, unhewn blocks of various kinds of "
        +"stone such as granite and marble.\n");
    add_item(({"tool","tools","chisel"}),"They appear "
        +"to be used in the carving of stone.\n");
    add_item(({"stepladder","ladder"}),"It looks weak, unable "
        +"to support more weight than a gnome or other small "
        +"race.\n");
	add_item(({"wall", "walls", "gneiss", "gneiss walls", "west wall"}),
	    "It looks like the walls are the same gneiss as elsewhere in the "
		+"museum, though it is difficult to be certain because there are so "
        +"many massive blocks of stone lined up against them.\n");
    add_item(({"door"}), "You can't see a door.\n");
    add_cmd_item(({"door", "west wall"}), ({"search" }), "It looks like "
	    +"there may be a door along the west wall but there are massive "
		+"slabs of stone blocking it.\n");		
    add_cmd_item(({"block", "slab"}), ({"shove", "heave", "shift", "walk"}), 
	    "@@access_block");
	add_item("sign", "A sign has been chiseled into the wall. It reads:\n"
	    +"     <pay>      To have a statue created in your image.\n"
        +"     <destroy>  To have your statue removed.\n\n");
	add_cmd_item("sign", "read", 
	    "A sign has been chiseled into the wall. It reads:\n"
	    +"     <pay>      To have a statue created in your image.\n"
        +"     <destroy>  To have your statue removed.\n\n");
	
    add_exit(STAT3, "east");

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );

    sculptor = clone_object(MUS+"sculptor");
    sculptor->move(TO);
    sculptor->arm_me();

    restore_object(STATUES);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
	add_prop(ROOM_M_NO_ATTACK, "The God Nitikas casts his protection upon "
	    +"this place and the priceless artifacts with in it.");
	add_prop(ROOM_M_NO_MAGIC_ATTACK, "The God Nitikas casts his protection "
	    +"this place and the priceless artifacts within it."); 
}

/* Called from the oter rooms of the
 * gallery to see which statues are there
 */
string *query_statues(int which)
{
    switch(which)
    {
        case 1: return statue1; break;
        case 2: return statue2; break;
        case 3: return statue3; break;
        case 4: return statue4; break;
        case 5: return statue5; break;
        case 6: return statue6; break;
        case 7: return statue7; break;
        case 8: return statue8; break;
        case 9: return statue9; break;
        case 10: return statue10; break;
        case 11: return statue11; break;
        case 12: return statue12; break;
        case 13: return statue13; break;
        case 14: return statue14; break;
        case 15: return statue15; break;
        default: return statue15; break;
    }
}

void set_statues(int which, string* values)
{
    switch(which)
    {
        case 1: statue1 = values; break;
        case 2: statue2 = values; break;
        case 3: statue3 = values; break;
        case 4: statue4 = values; break;
        case 5: statue5 = values; break;
        case 6: statue6 = values; break;
        case 7: statue7 = values; break;
        case 8: statue8 = values; break;
        case 9: statue9 = values; break;
        case 10: statue10 = values; break;
        case 11: statue11 = values; break;
        case 12: statue12 = values; break;
        case 13: statue13 = values; break;
        case 14: statue14 = values; break;
        case 15: statue15 = values; break;
    }
}

string access_block()
{
    int times = 0;
    times = TP->query_prop("_av_i_shoved_block");
	switch (times)
	{
	case 0..3:
	{
        write("You throw your weight against the block and succeed in "+
		   "making it move just a bit.\n"); 
		TP->add_prop("_av_i_shoved_block", times + 1);
		return "";
    }		
	case 4:
    {
        write("You succeed in shifting the block enough to reveal a "+
		   "door in the wall behind it and slip through it before "+
		   "anyone can see you.\n"); 
		TP->remove_prop("_av_i_shoved_block");
      	TP->move_living("X", BAZAAR+"intr/d_str2", 1, 0);
		return "";
	}
	default:
    return "";
    }	
}
	
init()
{
    ::init();
    add_action("do_pay","pay");
    add_action("do_reshuffle","reshuffle");
    add_action("remove","destroy");
}

/* Find a name in the arrays of statues, and
 * remove it and the statue desc if it is 
 * there. Returns 1 success, 0 failure
 */
int remove_statue(string name)
{
    int  nihil;

    if((nihil = member_array(name, statue1)) != -1)
    {
        statue1 = exclude_array(statue1, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT1))
            (STAT1)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue2)) != -1)
    {
        statue2 = exclude_array(statue2, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT2))
            (STAT2)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue3)) != -1)
    {
        statue3 = exclude_array(statue3, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT3))
            (STAT3)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue4)) != -1)
    {
        statue4 = exclude_array(statue4, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT4))
            (STAT4)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue5)) != -1)
    {
        statue5 = exclude_array(statue5, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT5))
            (STAT5)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue6)) != -1)
    {
        statue6 = exclude_array(statue6, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT6))
            (STAT6)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue7)) != -1)
    {
        statue7 = exclude_array(statue7, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT7))
            (STAT7)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue8)) != -1)
    {
        statue8 = exclude_array(statue8, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT8))
            (STAT8)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue9)) != -1)
    {
        statue9 = exclude_array(statue9, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT9))
            (STAT9)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue10)) != -1)
    {
        statue10 = exclude_array(statue10, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT10))
            (STAT10)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue11)) != -1)
    {
        statue11 = exclude_array(statue11, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT11))
            (STAT11)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue12)) != -1)
    {
        statue12 = exclude_array(statue12, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT12))
            (STAT12)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue13)) != -1)
    {
        statue13 = exclude_array(statue13, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT13))
            (STAT13)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue14)) != -1)
    {
        statue14 = exclude_array(statue14, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT14))
            (STAT14)->update_statues();
        return 1;
    }
    else if((nihil = member_array(name, statue15)) != -1)
    {
        statue15 = exclude_array(statue15, nihil, nihil+1);
        save_object(STATUES);
        if(find_object(STAT15))
            (STAT15)->update_statues();
        return 1;
    }
    return 0;
}

int do_reshuffle(string str)
{
    if(!TP->query_wiz_level())
        return 0;
    
    write("Let's get moving on those statues.\n");
    MUSLOG(CAP(TP->query_real_name())+" reshuffled the "
            +"statues.");
        
    int total_statues = 0; 
    string* statues_to_move = ({});
    
    // query_statues is one-indexed.
    for (int i = 1; i <= NUM_STATUE_ROOMS; i++)
    {
       total_statues += sizeof(query_statues(i)) / 2;
    }

    for (int i = 1; i <= NUM_STATUE_ROOMS; i++)
    {
        string* current_statues = query_statues(i);
        write(sprintf("Number of statues in room %d to start: %d\n",
              i, sizeof(query_statues(i))/2));
        while (sizeof(current_statues) / 2 > 
            total_statues / NUM_STATUE_ROOMS + 1)
        {
            statues_to_move += current_statues[0..1];
            current_statues = exclude_array(current_statues, 0, 1);
        }
        set_statues(i, current_statues);
        write(sprintf("Number of statues in room %d now: %d\n",
              i, sizeof(query_statues(i))/2));
    }
    write(sprintf("I will move %d statues.\n", sizeof(statues_to_move) / 2));
    
    for (int i = 1; i <= NUM_STATUE_ROOMS; i++)
    {
        string* current_statues = query_statues(i);
        write(sprintf("Number of statues in room %d to start: %d\n",
              i, sizeof(query_statues(i))/2));
        while (sizeof(current_statues) / 2 <
            total_statues / NUM_STATUE_ROOMS + 1 && sizeof(statues_to_move))
        {
            current_statues += statues_to_move [0..1];
            statues_to_move = exclude_array(statues_to_move, 0, 1);
        }
        set_statues(i, current_statues);
        write(sprintf("Number of statues in room %d now: %d\n",
              i, sizeof(query_statues(i))/2));
    }
    write(sprintf("I have %d statues unmoved.\n", sizeof(statues_to_move) / 2));
    save_object(STATUES);    
    return 1;
}

/* Remove a statue of yourself from the
 * gallery, or of someone else if you
 * are a wiz and have a damn good reason.
 */
int remove(string str)
{
    string  name;

    NF("The sculptor does not seem to be here right now, so "
        +"you can't do that.\n");
    if(!present(sculptor))
        return 0;

    if(TP->query_wiz_level() && strlen(str))
    {
        write("Let's hope you have a good reason "
            +"for this.\n");
        MUSLOG(CAP(TP->query_real_name())+" removed the "
            +"statue of "+str+".");
        name = str;
    }
    else
        name = TP->query_real_name();

    NF("You do not have a statue made of yourself!\n");
    if(!remove_statue(name))
        return 0;

    MUSLOG(CAP(name)+" had the statue removed.");
    write("You tell the gnome that you would like to have "
       +"your statue removed from the gallry.\n");
    sculptor->command("say I will get rid of it as soon "
       +"as possible. I'm sorry you don't like my work.");
    return 1;
}

int do_pay(string str)
{
    int     *result;
    string   name, title,
             desc, ret, chk;
    object   who;

    NF("The sculptor does not seem to be here right now, so "
        +"you can't do that.\n");
    if(!present(sculptor))
        return 0;

    if(TP->query_wiz_level() && strlen(str) && find_living(str))
        who = find_living(str);
    else
        who = TP;

    name = who->query_real_name();
    if(member_array(name, statue1+statue2+statue3+statue4
      +statue5+statue6+statue7+statue8+statue9+statue10+statue11
      +statue12+statue13+statue14+statue15)
       != -1)
    {
        sculptor->command("say You already have a statue of "
            +"yourself made!");
        sculptor->command("say If you want a new one, you will "
            +"have to get me to 'destroy' the last one.");
        return 1;
    }

    result = pay(STAT_COST, TP);
    if(sizeof(result) == 1)
        return 0;

    MUSLOG(CAP(name)+" had a statue made.");
    STATSERV_LOG_EVENT("bazaar", "Statues added to Museum");
        sculptor->command("emote starts work on a statue.");

#if 0
//  Xar said that the titles should reflect all of the person's titles, not just one
    title = who->query_guild_title_occ();
    if(!strlen(title))
        title = who->query_guild_title_lay();
    if(!strlen(title))
        title = who->query_guild_title_race();

    if(who->query_wiz_level())
      title = who->query_title();

    if(!sscanf(title, "the%s", chk) &&
        !sscanf(title, "The%s", chk))
        title = "the "+title;

#endif

    title = who->query_title();

    if(strlen(title))
        title = CAP(name)+" "+title+".";
    else
        title = CAP(name)+".";

/*
    if(who->query_wiz_level())
        title = who->query_prefix()+" "+title;
*/


    desc = generate_desc(who)+"A plaque at the bottom of the statue "+
          "reads:\n"+title+"\n";

    sculptor->command("say If you decide you do not like the statue, you can always "
        +"come back to me and tell me to 'destroy' it.");

// Need to get some statues into room 15 to blocking the others for now.
    switch(15)
//  switch(random(16))  
    {
        case 0..1:
            statue1 = ({ name, desc }) + statue1;
            save_object(STATUES);
            sculptor->command("say I will put your statue at "
                +"the museum entrance south of here " 
                +"when it is completed.");
            if(find_object(STAT1))
            (STAT1)->update_statues();
            return 1;
            break;
        case 2:
            statue2 = ({ name, desc }) + statue2;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the room just south of here " 
                +"when it is completed.");
            if(find_object(STAT2))
            (STAT2)->update_statues();
            return 1;
            break;
        case 3 :
            statue3 = ({ name, desc }) + statue3;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the room just east of here " 
                +"when it is completed.");
            if(find_object(STAT3))
            (STAT3)->update_statues();
            return 1;
            break;
        case 4:		
            statue4 = ({ name, desc }) + statue4;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the room just north of here " 
                +"when it is completed.");
            if(find_object(STAT4))
            (STAT4)->update_statues();
            return 1;
            break;
        case 5:
            statue5 = ({ name, desc }) + statue5;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the gallery two rooms north of here when it "
				+"is completed.");
            if(find_object(STAT5))
                (STAT5)->update_statues();
            return 1;
            break;
        case 6:
            statue6 = ({ name, desc }) + statue6;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the central atrium three rooms north of here "
				+"when it is completed.");
            if(find_object(STAT6))
                (STAT6)->update_statues();
            return 1;
            break;
        case 7:
            statue7 = ({ name, desc }) + statue7;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the north wing of the musem, in the farthest "
                +"north room when it is completed.");
            if(find_object(STAT7))
                (STAT7)->update_statues();
            return 1;
            break;
        case 8:
            statue8 = ({ name, desc }) + statue8;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"east room of the the north wing of the museum "
				+"when it is completed.");
            if(find_object(STAT8))
                (STAT8)->update_statues();
            return 1;
            break;
        case 9:
            statue9 = ({ name, desc }) + statue9;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the east wing of the museum, along the northeast "
                +"wall when it is completed.");
            if(find_object(STAT9))
                (STAT9)->update_statues();
            return 1;
            break;
        case 10:
            statue10 = ({ name, desc }) + statue10;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the east wing of the museum, along the eastern "
                +"wall, when it is completed.");
            if(find_object(STAT10))
                (STAT10)->update_statues();
            return 1;
            break;
        case 11:
            statue11 = ({ name, desc }) + statue11;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the east wing of the gallery, along the south"
                +"east wall, when it is completed.");
            if(find_object(STAT11))
                (STAT11)->update_statues();
            return 1;
            break;
        case 12:
            statue12 = ({ name, desc }) + statue12;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the west wing of the museum, along the "
                +"southwest wall, when it is completed.");
            if(find_object(STAT12))
                (STAT12)->update_statues();
            return 1;
            break;
        case 13:
            statue13 = ({ name, desc }) + statue13;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the west wing of the museum, along the far "
                +"west wall, when it is completed.");
            if(find_object(STAT13))
                (STAT13)->update_statues();
            return 1;
            break;
        case 14:
            statue14 = ({ name, desc }) + statue14;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the west wing of the museum, along the north"
                +"west wall, when it is completed.");
            if(find_object(STAT14))
                (STAT14)->update_statues();
            return 1;
            break;
        case 15:
            statue15 = ({ name, desc }) + statue15;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the north wing of the museum, along the west "
                +"wall, when it is completed.");
            if(find_object(STAT15))
                (STAT15)->update_statues();
            return 1;
            break;
        default:
            statue15 = ({ name, desc }) + statue15;
            save_object(STATUES);
            sculptor->command("say I will put your statue in "
                +"the north wing of the museum, along the west "
                +"wall, when it is completed.");
            if(find_object(STAT15))
                (STAT15)->update_statues();
            return 1;
            break;
    }
}

/* Generate the description of the player */
string generate_desc(object who)
{
    string ret,
           sub,
          *dum,
           nihil,
           pro,
           pos,
           obj,
           a, b, c;
    int    i;

    pro = who->query_pronoun();
    pos = who->query_possessive();
    obj = who->query_objective();

    ret = "It is a statue made from "+material(who)
        +", depicting "+who->query_nonmet_name()+". ";
    ret += implode(explode(who->long(TO), "\n"), " ");

    if(sscanf(ret, "%shair is%s", nihil, nihil))
        ret = implode(explode(ret, CAP(pos)+" hair is"), 
              "The hair of the statue is crafted to appear");

    if(sscanf(ret, "%shas scars%s", nihil, nihil))
        ret = implode(explode(ret, CAP(pro)+" has scars"), 
              "Skillfully etched into the surface are scars");

    dum = explode(ret, ". ");
    for(i=0;i<sizeof(dum);i++)
    {
        if(sscanf(dum[i], CAP(pro)+" is an %s", nihil) ||
            sscanf(dum[i], CAP(pro)+" is a %s", nihil))
            dum[i] = "The statue shows that "+pro+" is "+LANG_ADDART(nihil);
        if(sscanf(dum[i], "%spresenting%s", nihil, nihil) ||
            sscanf(dum[i], "%sseems to be%s", nihil, nihil) ||
            sscanf(dum[i], "%svoice%s", nihil, nihil) ||
            sscanf(dum[i], "%smove%s", nihil, nihil))
            dum[i] = "";
        if(sscanf(dum[i], CAP(pro)+" looks%s", nihil))
            dum[i] = "The figure shows "+obj+" as looking"+nihil;
    }

    ret = implode(dum, ". ");
    ret = implode(explode(ret, "\n"), " ");

    /* Get rid of ugly extra stuff */
    ret = implode(explode(ret, "  "), " ");
    ret = implode(explode(ret, ". ."), ".");
    ret = implode(explode(ret, ". ."), ".");
    ret = implode(explode(ret, ".."), ".");
    ret = implode(explode(ret, " (open)"), "");
    ret = implode(explode(ret, " (closed)"), "");
    ret = implode(explode(ret, "!!"), "!");
    ret = implode(explode(ret, "!!"), "!");
    ret += "\n";
    return ret;
}

/* The stone and style of the statue is determined by
 * the primary guild of the player
 */
string material(object who)
{
    string  guild;

    guild = who->query_guild_name_occ();
    if(!guild)
        guild = who->query_guild_name_lay();
    if(!guild)
        guild = who->query_guild_name_race();
    if(!guild)
        guild = "foobar!";

    switch(guild)
    {
        case RANGER: return "sturdy dark granite that seems "
                     +"to have been worn down by rough weather"; break;
        case KNIGHT: return "heavy white marble, gleaming "
                     +"brightly in the light"; break;
        case GLAD:   return "creamy alabaster streaked with reddish "
                     +"jasper";
        case ANGMAR: return "roughly formed gneiss, heavy "
                     +"and thick"; break;
        case VAMP:   return "dark, shadowy obsidian, which seems "
                     +"to absorb all the light cast upon it"; break;
        case MONK:   return "smooth jayacinth, formed in soft and "
                     +"graceful curves"; break;
        case MYSTIC: return "pale blue stone, sparkling "
                     +"mysteriously in the soft light"; break;
        case MAGE:   return "menacing dark stone, covered "
                     +"in jagged edges and sharp corners"; break;
        case SHAD:   return "smooth stone of a deep blue-black hue, "
                     +"it flickers flame-like in the light"; break;
        case MINSTRIL: return "gleaming soft white stone, "
                     +"made in graceful arcs and curves"; break;
        case L_MONK: return "smooth brown jayacinth, formed in soft and "
                     +"graceful curves"; break;
        case L_ANGMAR: return "roughly formed gneiss, heavy "
                     +"and thick"; break;
        case SQUIRE: return "thick white marble that "
                     +"glimmers softly with a holy glow"; break;
        case HERALD: return "soft green jadestone, pale and "
                     +"beautiful"; break;
        case TRICK:  return "heavy and unwieldly granite, blackened "
                     +"and dark"; break;
        case DROW:   return "jet black obsidian, so dark that "
                     +"the light seems to be absorbed into it"; break;
        case DUNE:   return "pale granite, streaked with "
                     +"veins of light blue gemstone"; break;
        case TRAVEL: return "rough and careworn granite, that "
                     +"seems to have seen the ends of the world"; break;
        case THANAR: return "menacing dark stone, rough and "
                     +"heavy"; break;
        case ROCK:   return "professionally carved stone, dressed "
                     +"with creases and patterns"; break;
        case GRUNT:  return "massive and roughly formed "
                     +"blocks of granite"; break;
        case WILD:   return "smooth and soft limestone, "
                     +"pale and beautiful"; break;
        case INVENT: return "cleverly formed stone, covered with "
                     +"intricate and superfluous designs"; break;
        case ADV_HOB: return "soft, lumpish limestone"; break;
        default:
        return "professionally carved granite"; break;
   }
}
