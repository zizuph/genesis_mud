/*
 * This is the tattoo artist in Gelan.
 * Coded by Stexx/Khail, 1995. 
 */

inherit "/std/monster";
inherit "/lib/trade";
inherit "/std/act/action";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Immortal/std/domain.h"
#include "/d/Calia/gelan/tattoos/tattoo_defines.h"
#include "/d/Calia/gelan/tattoos/tattoo_data.h"

#define TATTOO_DAMAGE      -100
#define BURN_DAMAGE        -200
#define MIN_DIS            30
#define TATTOO_COST        1728
#define TATTOO_OBJECT_NAME "_stexxs_tattoo_object"
#define SPOUSE_DESIGN      43
#define TPQPR              TP->query_pronoun()
#define TPQO               TP->query_objective()
#define CQO                customer->query_objective()
#define CQP                customer->query_possessive()
#define CQPR               customer->query_pronoun()

string adj1, adj2, bodyloc, str1, str2;
int arg, busy, guild_passed, design, i, *arr, error;
object shadow, customer, tob;
string remove_where;

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("budda");
    add_name("artist");
    set_race_name("human");
    set_title("the Body Artist");
    set_adj("smiling");
    set_long("This is Smiling Budda, the Body Artist.  He is a hefty " +
        "fellow, who looks like he could break someone in two fairly " +
        "quickly.  He looks like he is waiting for you to decide " +
        "something.\n");
    set_gender(0);
    set_alignment(300);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    default_config_npc(random(5)+55);
    set_base_stat(SS_CON,random(40)+56);
    set_base_stat(SS_STR,random(6)+88);
    set_hp(10000);
    set_skill(SS_WEP_CLUB, random(5)+66);
    set_skill(SS_DEFENCE, random(33)+66);
    set_skill(SS_AWARENESS, random(10) + 50);
    set_tell_active(1);
    set_chat_time(12);
    add_chat("I am the master of body art.");
    add_chat("You want a tattoo don't you?");
    add_chat("Read the sign, and examine the pictures, they're important.");
    add_act("@@scream_noise");
    add_act("emote sighs.");
    add_act("emote taps his fingers on the counter.");
    add_act("emote doodles on a piece of paper.");
    config_default_trade();
}

void
intro_me2(string who)
{
    int r;
  
    r = random(3);
    if (r == 0) 
        command("say Hello, " + capitalize(who)+ ".");
    else if (r == 1)
        command("say Welcome!");
    else if (r == 2)
        command("say Greetings, " + capitalize(who) + ".");
}

void
add_introduced(string who)
{
  set_alarm(1.0, 0.0, &command("introduce me"));
  set_alarm(2.0, 0.0, &intro_me2(who));
}

void
do_bow(object actor)
{
    if (objectp(actor))
        command("bow " + actor->query_real_name());
    else
        command("bow");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &do_bow(actor));
}

void
scream_noise(string what)
{
    if (!what) what = "a scream from the back room";
        tell_room(environment(this_object()),QCTNAME(this_object()) + 
            " chuckles when he hears "+what+".\n");
}

/*
 * Function name: recover
 * Description: Allows players to recover missing tattoo objects
 * Arguments: str - a string, must be 'tattoo' to activate.
 */
int
recover(string str)
{
    NF("Recover what? Recover tattoo, maybe?\n");

    if(str != "tattoo")
        return 0;

    if(present(TATTOO_OBJECT_NAME, TP))
    {
        NF("");
        command("peer "+TP->query_name());
        command("say Is it daft, ye are? There's nothing wrong with the " +
            "tattoo ye've got.");
        return 0;
    }
  
    if(file_size(TATTOO_RECOVER) < 0)
    {
        NF("");
        command("say Who are ye trying to fool, ye don't have any tattoos "+
            "to recover, bud!");
        return 0;
    }

    command("ask "+TP->query_real_name()+" Let's just keep this between " +
        "us, ok?");
    TP->catch_msg(QCTNAME(TO)+" gives you a subtle poke nobody else " +
         "notices, and much to your delight you realize you're tattood " +
         "again!\n");
    clone_object(TATTOO_OBJECT)->move(TP);
    return 1;
}


void
clear_customer(object c)
{
    if (busy && (c == customer)) 
        busy = 0; 
}


/*
 * Function Name : order
 *
 * Description : Called for players to order tattoos.
 *
 * Arguments : string str - A string of the form 
 *                          '<adj1> <adj2> <num> <location>', which is
 *                          then broken down into components with sscanf
 *
 * Returns : 0 - failure.
 *           1 - success.
 */
int
order(string str)
{
    string design_str;
    object marriage_ring, spouse;
    int spouse_passed;

  /* Is artist busy? */
    if (busy) { 
        if (objectp(customer) && objectp(present(customer, environment(TO))))
        {
            TP->catch_msg(QCTNAME(TO)+" is already busy with "+
                  QCTNAME(customer) + ", try again in a minute.\n");
            NF("");
            return 0;
         }
         else  
             customer = TP; 
     }
     else {
        busy = 1;
        customer = TP;
    }

  /* Did player use an argument to order with? */
    if(!strlen(str))
    {
        command("say Order what?\n");
        busy = 0;
        return 1;
    }
  
  /* What kind of arguments did we get */
    if(sscanf(str,"%s %s %d %s",adj1, adj2, design, bodyloc) < 3)
    {
        if(sscanf(str,"%s %s",adj1, adj2) == 2)
        {
/*
  write("guild/club tattoo, adj1 = "+adj1+", adj2 = "+adj2+"\n");
 */ 
    if (adj1 == "spouse")
    {
        if (!(marriage_ring = present("_emerald_marriage_ring_",customer)))
        {
            command("say You aren't even married!");
            busy = 0;
            return 1;
        }
        if (!(spouse = present(marriage_ring->query_person(),environment(TO))))
        {
            command("say I can't tattoo someone who isn't here, fool.");
            busy = 0;
            return 1;
        }
        
        command("say Ahh, a tattoo of yer loved one, how quaint.");
        bodyloc = adj2;
        design = SPOUSE_DESIGN;
        if (!stringp(spouse->query_adjs()[0]))
            adj1 = "";
        else
            adj1 = spouse->query_adjs()[0] + " ";
        if (!stringp(spouse->query_adjs()[1]))
            adj1 += "";
        else
            adj1 += spouse->query_adjs()[1] + " ";
        adj1 += spouse->query_gender_string() + " " +
            spouse->query_race_name();
        adj2 = spouse->query_name();
        spouse_passed = 1;
    }
    else
    {
        if (member_array(adj1,m_indexes(guild_tattoos)) < 0)
        {
            write(adj1+" is not a listed guild.\n");
            busy = 0;
            return 1;
        }
        if (member_array(guild_tattoos[adj1][0],
            customer->query_cmdsoul_list()) < 0)
        {
            write("You are not a member of that organization.\n");
            busy = 0;
            return 1;
        }
        guild_passed = 1;
        bodyloc = adj2;
        design = guild_tattoos[adj1][3];
        adj2 = guild_tattoos[adj1][2];
        adj1 = guild_tattoos[adj1][1];
    }
  }
  }

/*
  write("Got "+adj1+", "+adj2+", "+design+" and "+bodyloc+"\n");
 */

    if(design != SPOUSE_DESIGN && 
        (!strlen(adj1) || member_array(adj1,tattoo_adj) <  0))
    {
        command("say I can't tattoo that first adjective, "+adj1+", "+
            "read the sign and stop wasting my time!");
        busy = 0;
        return 1;
    }

    if(design != SPOUSE_DESIGN &&
        (!strlen(adj2) || member_array(adj2,tattoo_adj) < 0))
    {
        command("say I can't tattoo that second adjective, "+adj2+", "+
            "read the sign and stop wasting my time!");
        busy = 0;
        return 1;
    }

    if(design < 0 || sizeof(tattoo_design)<= design)
    {
        command("sigh wearily");
        command("say How dumb are you?  Give me a design number from the "+
            "list!");
        busy = 0;
        return 1;
    }

    for (i = 0; i < sizeof(m_indexes(guild_tattoos)); i++)
    {
        if (!guild_passed && design == m_values(guild_tattoos)[i][3])
        {
            write("That's a reserved tattoo, read the sign on how to get " +
                "one.\n");
            busy = 0;
            return 1;
        }
    }
    guild_passed = 0;

    if (!strlen(bodyloc) || !tattoo_cover[bodyloc])
    {
        command("think a new line of work.");
        command("say Give me a break and read the signs before ordering "+
            "again, I can't put a tattoo on your "+bodyloc+".");
        busy = 0;
        return 1;
    }

    if (design == SPOUSE_DESIGN && !spouse_passed)
    {
        command("say Sorry, that's the design for the spouse tattoos.  " +
            "Read the sign to see the right way to get one.");
        busy = 0;
        return 1;
    }

    if (spouse_passed)
        spouse_passed = 0;

    design_str = MASTER_TATTOO->make_design(design, adj1, adj2);

    command("say Okay, you want me to give you "+design_str+
        " on your "+tattoo_cover[bodyloc][1]+", correct? (yes or no).");
    input_to("get_tattoo");
    return 1;
}


/* 
 * I changed this to make sure the player is the customer and 
 * Bubba is busy with him/her at the beginning - Maniac 
 */ 
int
get_tattoo(string str)
{

    if (!busy || !objectp(customer) || (TP != customer) || 
       !objectp(present(customer, environment(TO)))) 
        return 0;

    FIXEUID;
    if (str != "yes" && str != "no")
    {
        command("say It's not a trick question, you know, just yes or no.  "+
            "Which part exactly has you confused?");
        input_to("get_tattoo");
        return 1;
    }

    if (str == "no")
    {
         command("sigh pitifully");
         command("say Well, I had you pegged as a wimp anyway.  Come back "+
             "when you've grown a backbone.");
         NF("");
         busy = 0;
         return 0;
    }

    arg = 0;

    if (!present(TATTOO_OBJECT_NAME,customer))
    {
        tob = clone_object(TATTOO_OBJECT);
        tob->move(customer);
    }
    else
        tob = present(TATTOO_OBJECT_NAME,customer);

  /* This little routine is just to make sure that the */
  /* player's current tattoo object is one of those from */
  /* the currently loaded master of tattoo.c, reduces the */
  /* problems of adding new info to the tattoo_data.h file. */
    if (member_array(tob,
        object_clones(find_object(TATTOO_OBJECT))) < 0)
    {
        tob->remove_object();
        tob = clone_object(TATTOO_OBJECT);
        tob->move(customer);
    }

    if (arg != -6)
    {
        arg = tob->add_tattoo(adj1, adj2, design, bodyloc);
/*
    write("Called add_tattoo and got "+arg+"\n");
 */
    }

  /* if the customer doesn't have the dis, everyone else gets a laugh */
    if (arg == 1 && customer->query_stat(SS_DIS) < MIN_DIS)
    {
        customer->catch_msg("As " + QTNAME(TO) + " approaches you, you " +
            "get a good look at the needle and suddenly realize that " +
            "you don't have the guts for this kind of thing and run for " +
            "all you're worth!\n");
        tell_room(environment(TO), "As " + QTNAME(TO) + " approaches " +
            QTNAME(customer)+", "+ QTNAME(customer) + " gets a sudden look " +
            "of horror in " + CQP + " eyes, then runs out as fast as " +
            CQP + " legs can carry " + CQO + "!\n", ({customer}));
        customer->command("scream");
        customer->command("panic");
        customer->command("west");
        tob->remove_tattoo(bodyloc);
        arg = -7;
    }
    switch(arg)
    {
        case 1:
            command("say Ok, now the fun starts!\n");
        break;

        case 0:
            command("say Ye've already got a tattoo there, bub, I can't " +
                "just draw over it ya know.\n");
        break;
    
        case -1:
            command("say Any more tattoos and you risk blood poisoning, "+
                "sorry.\n");
        break;

        case -2:
            command("say I'm afraid I can't tattoo that first adjective, "+
                adj1+".\n");
        break;

        case -3:
            command("say I'm afraid I can't tattoo that second adjective, "+
                adj2+".\n");
        break;

        case -4:
            command("say There doesn't appear to be any tattoo design "+
                "number "+design+".\n");
            break;

        case -5:
            command("say I can't put a tattoo on your "+bodyloc+".\n");
        break;

        case -6:
            command("say Hmm, I don't seem to be able to give you a tattoo "+
                "for some reason.  Better report it.");
        break;
    
        case -7:
            command("shout Coward!");
            command("grin");
        break;
        default:
            command("say Seems I'm a bit buggy, better report me.\n");
        break;
    }


  /* If for some reason the player couldn't get a tattoo after all, */
  /* remove the tattoo object */
    if (arg != 1)
    {
        if (!tob->query_tattoos() || !sizeof(tob->query_tattoos()))
        {
            tob->clean_out_tattoos();
        }
        busy = 0;
        return 1;
    }

    if (sizeof(arr = pay(TATTOO_COST, customer, "", 0, 0, "")) == 1)
    {
      tob->remove_tattoo(bodyloc);
      command("say Whaddya think, I'm running a charity business here?  " +
          "Come back when ye've got some coins in yer purse!");
      NF(""); 
      busy = 0;
      return 0;
    }

    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            command("say Feeling lucky trying to pass me funny money?  Try "+
                "it again and I'll use the old rusty needles.");
            tob->remove_tattoo(bodyloc);
            if (!tob->query_tattoos() || !sizeof(tob->query_tattoos()))
            {
                tob->clean_out_tattoos();
            }
        NF("");
        busy = 0;
        return 0;
        }
    }

    customer->catch_msg(QCTNAME(TO)+" grins evilly and grabs you by the " +
        "wrist, dragging you over to a workbench and slams you down.  " +
        "You scream in surprise at the pain when his obviously dull " +
        "needle breaks your skin.  Luckily, it's all over soon, and you " +
        "stand up rubbing your freshly decorated and very sore " +
        tattoo_cover[bodyloc][1]+".\n");
    tell_room(environment(TO),QCTNAME(TO)+" grins evilly and grabs "+
        QCTNAME(customer)+" by the wrist, dragging "+CQO+" over to a " +
        "workbench and slams "+CQO+" down.  "+QCTNAME(customer)+" screams " +
        "in surprise at the pain from what sounds like a dull needle as " + 
        QCTNAME(TO) + " starts working.  Soon, it's all over, and " +
        QCTNAME(customer)+" rises from the table, rubbing "+CQP+" freshly " +
        "decorated and apparently sore "+tattoo_cover[bodyloc][1]+".\n",
        ({customer}));
    customer->heal_hp(TATTOO_DAMAGE);
    command("say There, that wasn't so bad now, was it?\n");
    command("laugh");
    command("say Boy, I love this job.\n");

    str1 = text(arr[4..2*4-1]);
    if (!str1)
        str1 = "nothing";
    str2 = text(arr[0..4-1]);

    TP->catch_msg("You pay " + QTNAME(TO) + " " + str2 +
        ", getting back " + str1 + " in change.\n");
    say(QCTNAME(customer) + " pays " + QTNAME(TO) + " " + str2 +
        ", getting back " + str1 + " in change.\n");

    busy = 0;
    return 1;
}
                       

int 
burn(string str)
{
    string burnwho;
    string *arg;

  /* Is artist busy? */
    if (busy) { 
        if (objectp(customer) && objectp(present(customer, environment(TO))))
        {
            TP->catch_msg(QCTNAME(TO)+" is already busy with "+
                  QCTNAME(customer) + ", try again in a minute.\n");
            NF("");
            return 0;
         }
         else  
             customer = TP; 
     }
     else {
        busy = 1;
        customer = TP;
    }


    NF("Burn what?\n");

    if (!strlen(str))
    {
        busy = 0;
        return  0;
    }

    arg = explode(str," ");
/*
   write("arg[0] = "+arg[0]+"\narg[1] = "+arg[1]+"\narg[2] = "+arg[2]+"\n");
 */

    if (sizeof(arg) != 3)
    {
        busy = 0;
        return 0;
    }

    if (arg[0] != "tattoo")
    {
        busy = 0;
        return 0;
    }

    if (arg[1] != "on")
    {
        command("say Stop jibbering, fool, burn tattoo on what body spot?");
/*
    write("arg[1] = "+arg[1]+"\n");
 */
        NF("");
        busy = 0;
        return 0;
    }

    if (!tattoo_cover[arg[2]])
    {
        command("grumble");
        command("say Why are you intent on wasting my time?  If you want " +
            "me to burn off a tattoo, you'll have to give me a location " +
            "from the list.");
        NF("");
        busy = 0;
        return 0;
    }

    if (!present(TATTOO_OBJECT_NAME, customer))
    {
        command("rolleyes");
        command("say You don't even have a tattoo you fool!");
        busy = 0;
        NF("");
        return 0;
    }

    tob = present(TATTOO_OBJECT_NAME, customer);

    if (member_array(SUBLOC+arg[2],tob->query_tat_sublocs()) < 0)
    {
        command("sigh wearily");
        command("say But you don't even have a tattoo on that location!  " +
            "Read the signs and try again.");
        NF("");
        busy = 0;
        return 0;
    }

    command("say Ahh, ok.  Ye want me to burn the tattoo from your "+
        tattoo_cover[arg[2]][1]+", correct? (yes or no).");
    remove_where = arg[2];
    input_to("burn_it");
    return 1;
}

int
burn_it(string str)
{
    object scar;

    if (!busy || !objectp(customer) || (TP != customer) || 
       !objectp(present(customer, environment(TO)))) 
        return 0;

    if (str != "yes" &&  str != "no")
    {
        command("say It's not a tough question, ya fool, yes or no?");
        input_to("burn_it");
        return 1;
    }

    if (str == "no")
    {
        command("sigh");
        command("say If you insist.  Too bad, I like the screaming.");
        NF("");
        busy = 0;
        return 0;
    }

    if (str == "yes")
    {
        if (sizeof(arr = pay(TATTOO_COST, customer, "", 0, 0, "")) == 1)
        {
            command("say Whaddya think, I'm running a charity business " +
                "here?  Come back when ye've got some coins in yer purse!");
            busy = 0;
            return 0;
        }

      if (error = arr[sizeof(arr) - 1])
      {
          if (error < -1)
          {
              command("say Feeling lucky trying to pass me funny money?  " +
                  "Try it again and I'll use the old rusty needles.");
          }
          NF("");
          busy = 0;
          return 0;
      }

    command("cackle");
    command("say I love this almost as much as putting tattoos on.");
    tell_room(environment(TO),QCTNAME(TO)+" rummages around for a moment, "+
        "and comes up with a jar of foul-smelling salves.  Smiling evilly, "+
        "he looks around a bit more and finds a pair of heavy gloves that "+
        "he hurriedly pulls on.\n",({customer}));
    customer->catch_msg(QCTNAME(TO)+" grabs you and slaps the steaming " +
        "salve onto your "+tattoo_cover[remove_where][1]+".  The salve " +
        "immediately starts to hiss and bubble, causing an immense amount " +
        "of pain.\n");
    tell_room(environment(TO),QCTNAME(TO)+" grabs "+QCTNAME(customer)+" and " +
        "slaps the steaming salve onto "+CQP+" "+
        tattoo_cover[remove_where][1]+".  The salve immediately starts " +
        "to hiss and bubble, and looks really, _really_  painful.\n",
        ({customer}));
    customer->heal_hp(BURN_DAMAGE);
    customer->command("scream");
    tell_room(environment(TO),"The salve stops steaming, and has vanished "+
        "entirely, having burned off the tattoo ink, leaving a ugly red "+
        "blotch.\n");
    tob->remove_tattoo(remove_where);
    scar = clone_object(TATTOO_SCAR);
    scar->set_location(remove_where);
    scar->move(customer);

    str1 = text(arr[4..2*4-1]);
    if (!str1)
        str1 = "nothing";
    str2 = text(arr[0..4-1]);

    customer->catch_msg("You pay " + QTNAME(TO) + " " + str2 +
        ", getting back " + str1 + " in change.\n");
    say(QCTNAME(customer) + " pays " + QTNAME(TO) + " " + str2 +
        ", getting back " + str1 + " in change.\n");
    }
    busy = 0;
}

void
init_living()
{
    ::init_living();
    add_action(order,"order");
    add_action(burn,"burn");
    add_action(burn,"tburn");
    add_action(recover,"recover");
    add_action(recover,"restore");
}
