/*
 * File Name        : pirate_cave.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : This is the joinroom of the pirates.
 *                    It has two methods. Become() and Leave().
 *
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{
    set_short("Throne room of the Dargaard Keep");
    set_long("@@long_descr");

    add_exit("somewhere", "west");
    
}

string
long_descr()
{ 
   return "Throne room in the Dargaard Keep.\n";
}

int
become(string str)
{
    object sh, sh2;
    mixed why;
    int success;
    string adjs;

    if(!str)
    {
        notify_fail("Become what? A death knight?\n");
        return 0;
    }

    if (L(str) == "knight" || L(str) == "a knight" ||
        L(str) == "a death knight" ||
        L(str) == "death knight")
    {
        if (TP->query_guild_member("occuptional") == 1 ||
            TP->query_guild_name_occ("layman") == 1)
        {
            write("Becoming a Death Knight requires both time and dedication.\n"+
                  "At the moment you are too busy with other guilds to become "+
                  "a servant of Lord Soth.\n");
            return 1;
        }

        if(sizeof(TP->query_prop(DK_JOIN_ADJS)))
           adjs = TP->query_prop(DK_JOIN_ADJS)[0]+","+
                  TP->query_prop(DK_JOIN_ADJS)[1];


        /* Clone the occ shadow */
        setuid();
        seteuid(getuid());

        sh = clone_object(GUILD_SHADOW);
        
        if (stringp(why = sh->acceptable_member(TP)))
        {
            write(why);
        }
        else
        {
    	    switch (sh->add_occ_shadow(adjs, TP))
    	    {
    	        case 1:
                    success = 1;
                break;

    	        case -4:
                    write("Becoming a Death Knight requires both will and dedication.\n"+
                          "You are unable to join the guild (occ).\n");
                break;
    
	        default:
	            write("An error has prevented you from joining.\n");
	        break;
            }
        }

    if (success != 1)
        sh->remove_shadow();
    else
        setuid();
        seteuid(getuid());

        sh2 = clone_object(GUILD_SHADOW2);
         
        if (stringp(why = sh2->acceptable_member(TP)))
        {
            write(why);
        }
        else
        {
    	    switch (sh2->add_lay_shadow(TP))
    	    {
    	        case 1:
                      find_living(GUILD_WIZARD)->catch_msg("\n\n"+TP->query_name() +
                                  " has become a Death Knight!\n\n");
              
                      set_alarm(0.0,0.0, &write("Suddenly flames leap from the floor "+
                                                " and engulf you!\n"));
                      set_alarm(3.0,0.0, &write("The flesh is torn from your skin!\n"));
                      set_alarm(4.0,0.0, &write("You fall to the ground in agony.\n"));
                      set_alarm(5.0,0.0, &write("You die.\n"));
              
                      write_file(GUILD_LOG+"dknight_log.txt", TP->query_name() + " joined " + 
                                 extract(ctime(time()), 4, 15)+
                                 ", StatAvg: "+TP->query_average_stat()+
                                 ", Race: "+TP->query_race()+
                                 ", Align: "+TP->query_alignment()+"\n");
                    return 1;

    	        case -4:
                    write("Becoming a Death Knight requires both will and dedication.\n"+
                          "You are unable to join the guild (occ).\n");
                break;
    
	        default:
	            write("An error has prevented you from joining.\n");
	        break;
            }
            sh2->remove_shadow();
        }
    }
    return 1;
}

int
leave(string str)
{
    if (L(str) == "knights")
    {

        if (!TP->query_guild_member(GUILD_NAME))
        {
            write("But you aren't a member of this guild!\n");
            return 1;
        }
    
   
        set_alarm(0.0,0.0, &write("You beg Paladine for forgiveness.\n"));
        set_alarm(3.0,0.0, &write("Paladin grants you wish!\n"));
        set_alarm(3.5,0.0, &write("You die.\n"));

        TP->remove_occ_member();
        TP->remove_lay_member();
    
        write_file(GUILD_LOG+"dknight_log.txt", TP->query_name() + " left " + 
                   extract(ctime(time()), 4, 15)+
                   ", StatAvg: "+TP->query_average_stat()+
                   ", Race: "+TP->query_race()+
                   ", Align: "+TP->query_alignment()+"\n");
    }

    return 1;
}


int
select(string str)
{
    string adj1,adj2,padj1,padj2;
    string *my_own;
    int index;

    if(!str)
    {
       NF("You must enter two adjectives in the form of:\n"+
       "select (adjective 1) and (adjective 2). They must be from the "+
       "list, or one of your current ones.\n");
        return 0;
    }

    if(str == "clear")
    {
        TP->remove_prop(DK_JOIN_ADJS);
        write("Cleared.\n");
        return 1;
    }
    NF("You must enter two adjectives in the form of:\n"+
       "select (adjective 1) and (adjective 2). They must be from the "+
       "list, or one of your current ones.\n");
    if(sscanf(str,"%s and %s",adj1,adj2) != 2)
        return 0;
    my_own = TP->query_adj(1);
    if( (index = member_array(adj1,my_own)) != -1)
        padj1 = my_own[index];
    if( (index = member_array(adj2,my_own)) != -1)
        padj2 = my_own[index];
    /* Yes, you could select both of your own, but no good to do so */
    if(  (index = member_array(adj1,DK_ADJ_LIST)) != -1)
        padj1 = DK_ADJ_LIST[index];
    if(  (index = member_array(adj2,DK_ADJ_LIST)) != -1)
        padj2 = DK_ADJ_LIST[index];
    NF("You did not select one from the list or from your own current "+
    "adjectives.\n");
    if(!stringp(padj1))
        return 0;
    if(!stringp(padj2))
        return 0;
    NF("They cannot be the same for both!\n");
    if(padj1 == padj2)
        return 0;
    TP->add_prop(DK_JOIN_ADJS,({padj1,padj2}));
    write("Selected: "+padj1+" and "+padj2+"\n");
    write("When you join, they will be taken into effect.\n");
    return 1;
}


int
list(string str)
{
    NF("List what?\n");
    if(str != "adjectives")
        return 0;
    TP->catch_msg("You can select these adjectives:\n"+
                  "eyeless, deathly, glowing-eyed, "+
                  "ember-eyed, zombie-like, "+
                  "empty-eyed,  rancid, unholy, "+
                  "ghastly, foul, decaying, cruel, "+
                  "skeletal, gloomy, sullen, "+
                  "ominous, ashen, grim, eerie, "+
                  "haggard, spectral, ghostly, "+  
                  "macabre, soul-less, gaunt, "+   
                  "horrible, cold, ancient, "+    
                  "ashen, atrocious, baleful, "+      
                  "blackened, burned, charred, "+    
                  "cruel, demonic, depraviated, "+   
                  "disgraced, disliked, fabled, "+  
                  "feared, gaunt, grisly, "+  
                  "gruesome, harmful, horrible, "+
                  "intense, loyal, mythical, "+  
                  "ominous, orange-eyed, osseously, "+
                  "potent, puissant, reticent, "+
                  "rotten, scragy, scrawny, "+
                  "silent, skinny, soul-less, "+
                  "suffering, sullen, taciturning, "+
                  "tall, thin, tormented, "+
                  "towering, unholy.\n");

    return 1;
}

void
init()
{
    ::init();
    ADA("list");
    ADA("select");
    ADA("become");
    ADA("leave");
}
