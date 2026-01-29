
/**  DARGAARD KEEP ROOM **/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>

inherit GUILD_IN;

#define I_AM_KNEELING  "_obj_i_am_kneeling"

object cage = GUILD_ROOM + "cage";
object soth, death_flag, dk;
object player, ob;
object *obj;
string first_adj, second_adj;


/* prototypes */
void do_step1();
void do_step2();
void do_step3();
void do_step4();
void do_step5();
void do_step6();
void do_step7();
void do_step8();
void do_step9();
void do_step10();
void do_step11();
void do_step12();
void do_step13();
void do_step14();
void become_dk(object obj);


void
reset_dargaard_room()
{
    if(!objectp(soth))
    {
  	    soth = clone_object(GUILD_NPC + "soth");
        soth->move(TO);
    }
}

void
create_dargaard_room()
{
    set_short("Hallway in Dargaard Keep");
    set_long("You carefully enter an ancient throne room underneath "+
             "Dargaard Keep. A heavy strench of rotten flesh and "+
             "burnt skin surrounds you. The once pure crystal walls "+
             "have become black as the night, and a beautiful carved "+
             "wooden throne stands next to the south wall. Torches and "+
             "pillars together with a torn carpet makes a narrow way "+
             "towards the wooden throne. An old solamnic blade has been "+
             "attached to the wall just above the throne. The only way "+
             "out of here is to the north.\n");

    add_exit(GUILD_ROOM + "room6","north",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

int
initiate(string str)
{
    if (TP->query_real_name() != "elmore")
//     (!TP->query_guild_member(GUILD_NAME) ||

//        !TP->test_bit("ansalon",3,10))
        write("What ?\n");
    else
    {
        if(strlen(str) == 0)
        {
            notify_fail("Whom do you wish to initiate into Lord Soth's "+
                        "undead army ?\n");
            return 0;
        }

        if(strlen(str))
        {
            if(!sizeof(obj = PARSE_THIS(str, "[the] %l")))
            {
                notify_fail("Whom do you wish to initiate into Lord Soth's "+
                            "undead army ?\n");
                return 0;
            }
            ob = obj[0];
        }

        if (ob->query_guild_member(GUILD_NAME))
        {
            notify_fail("But "+HE(ob)+ " is already serving Lord Soth.\n");
            return 0;
        }
/*
        if (!ob->query_prop(I_AM_KNEELING))
        {
            notify_fail("The initiate must be kneeling to preform the "+
                        "ceremony.\n");
            return 0;
        }
*/

        if (ob->query_guild_member("occuptional") == 1 ||
            ob->query_guild_name_occ("layman") == 1)
        {
            notify_fail("Becoming a Death Knight requires both time and dedication.\n"+
                        "At the moment ythat person is too busy with other guilds to become "+
                        "a servant of Lord Soth.\n");
            return 0;
        }

        
        set_alarm(3.0, 0.0, &do_step1());
        set_alarm(6.0, 0.0, &do_step2());
        set_alarm(9.0, 0.0, &do_step3());
        set_alarm(12.0, 0.0, &do_step4());
        set_alarm(15.0, 0.0, &do_step5());
        set_alarm(18.0, 0.0, &do_step6());
        set_alarm(21.0, 0.0, &do_step7());
        set_alarm(24.0, 0.0, &do_step8());
        set_alarm(27.0, 0.0, &do_step9());
        set_alarm(30.0, 0.0, &do_step10());
        set_alarm(33.0, 0.0, &do_step11());
        set_alarm(36.0, 0.0, &do_step12());
        set_alarm(39.0, 0.0, &do_step13());
        set_alarm(42.0, 0.0, &do_step14());

        return 1;
    }
    return 0;
}


void
do_step1()
{
        ob->add_prop(LIVE_I_NO_CORPSE, 1);
        write("\nYou say to Lord Soth: My Lord and Master we have found another "+
                    "being that wants to serve You. I humbly ask you to accept "+
                    HIM(ob)+ " into your ranks as one of your loyal servants.\n");
        say(QCTNAME(TP)+ " says to to Lord Soth: My Lord and Master we have found another "+
                    "being that wants to serve You. I humbly ask you to accept "+
                    HIM(ob)+ " into your ranks as one of your loyal servants.\n");
}

void
do_step2()
{
        write("You say to Lord Soth: Please free "+HIM(ob)+" from this mortal plane.\n");
        say(QCTNAME(TP) + " says to Lord Soth: Please free "+HIM(ob)+" from this mortal plane.\n");
}

void
do_step3()
{
        write("Lord Soth stands up from his throne.\n");
        say("Lord Soth stands up from his throne.\n");
}

void
do_step4()
{
        write("Lord Soth says: Very well. I shall free the wrench.\n");
        say("Lord Soth says: Very well. I shall free the wrench.\n");
}


void
do_step5()
{
        write("Lord Soth gets a firm grip around his solamnian greatsword.\n");
        say("Lord Soth gets a firm grip around his solamnian greatsword.\n");
}


void
do_step6()
{
        write("Lord Soth turns his red eyes at " +ob->query_the_name(TP)+ ".\n");
        say("Lord Soth turns his red eyes at you.\n");
}

void
do_step7()
{
        write("With a quick movement, Lord Soth stabs " +ob->query_the_name(TP)+
         " in the chest with his solamnian greatsword. Deep red blood begins "+
         "to stain the ground.\n");
        say("With a quick movement, Lord Soth stabs you in the chest "+
        "with his solamnian greatsword. The feel the cold steel entering "+
        "your body. Your warm deep red blood stains your armour and the ground.\n");
}

void
do_step8()
{
        write(ob->query_the_name(TP)+ " begins to gasp for air.\n");
        say("You begin to gasp for air.\n");
}


void
do_step9()
{
        write("Lord Soth opens the door to the iron cage.\n");
        say("Lord Soth opens the door to the iron cage.\n");
}


void
do_step10()
{
        write("With one graceful movement Lord Soth throws "+ob->query_the_name(TP)+" into "+
        "the iron cage.\n");
        say("With one graceful movement Lord Soth throws you into "+
        "the iron cage.\n");
 
        ob->move_living("M",GUILD_ROOM + "cage");
}


void
do_step11()
{
        write("Lord Soth closes the door to the iron cage.\n");
        say("The iron door slams shut.\n");

        write("Lord Soth smiles sadistically.\n");
}


void
do_step12()
{
        cage->start_initiation(ob);

        write("The iron chains connecting the cage to the ceiling create a loud "+
              "shreaking sound as the cage continues its decent...\n");
        say("The iron chains connecting the cage to the ceiling create a loud "+
            "shreaking sound as the cage continues its decent...\n");
}


void
do_step13()
{
        write("As "+ob->query_the_name(TP)+" hits the molten lava, "+HIS(ob)+" blood begins to boil and "+HIS(ob)+ 
                                 "skin melts from "+HIS(ob)+" bones.\n");
        say("As "+ob->query_the_name(TP)+" hits the molten lava, "+HIS(ob)+" blood begins to boil and "+HIS(ob)+ 
                                 "skin melts from "+HIS(ob)+" bones.\n");

}


void
do_step14()
{
        write("Just meters from the maerlstrom, "+ob->query_the_name(TP)+ 
              " screams out in pain, as "+HIS(ob)+ "skin starts to boil and peel "+
              "away. "+HIS(ob)+" solamnian armour starts to glow in an orange colour.\n");
        say("Just meters from the maerlstrom,  "+ob->query_the_name(TP)+ 
              " screams out in pain, as "+HIS(ob)+ "skin starts to boil and peel "+
              "away. "+HIS(ob)+" solamnian armour starts to glow in an orange colour.\n");

        write(ob->query_the_name(TP) + " burns to death.\n");
        say(ob->query_the_name(TP) + " burns to death.\n");

}

int
become_dk(object obj)
{
    object sh, sh2;
    mixed why;
    int success;
    string adjs;

    if (obj->query_guild_member("occuptional") == 1 ||
        obj->query_guild_name_occ("layman") == 1)
    {
        write("Becoming a Death Knight requires both time and dedication.\n"+
              "At the moment you are too busy with other guilds to become "+
              "a servant of Lord Soth.\n");
        return 1;
    }
    obj->add_prop(DK_JOIN_ADJS,({first_adj,second_adj}));

    if(sizeof(obj->query_prop(DK_JOIN_ADJS)))
      adjs = obj->query_prop(DK_JOIN_ADJS)[0]+","+
             obj->query_prop(DK_JOIN_ADJS)[1];


    /* Clone the occ shadow */
    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);
      
    if (stringp(why = sh->acceptable_member(obj)))
        write(why);
    else
    {
        switch (sh->add_occ_shadow(adjs, obj))
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
         
        if (stringp(why = sh2->acceptable_member(obj)))
            write(why);
        else
        {
    	    switch (sh2->add_lay_shadow(obj))
    	    {
    	        case 1:
                      find_living(GUILD_WIZARD)->catch_msg("\n\n"+obj->query_name() +
                                  " has become a Death Knight!\n\n");
              
                      write_file(GUILD_LOG+"dknight_log.txt", obj->query_name() + " joined " + 
                                 extract(ctime(time()), 4, 15)+
                                 ", StatAvg: "+obj->query_average_stat()+
                                 ", Race: "+obj->query_race()+
                                 ", Align: "+obj->query_alignment()+"\n");
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
        //TP->remove_prop(DK_JOIN_ADJS);
        first_adj = "";
        second_adj = "";
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
  //  TP->add_prop(DK_JOIN_ADJS,({padj1,padj2}));
    first_adj = padj1;
    second_adj = padj2;
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
//  ADA("become");
    ADA("initiate");
    ADA("list");
    ADA("leave");
    ADA("select");
}

