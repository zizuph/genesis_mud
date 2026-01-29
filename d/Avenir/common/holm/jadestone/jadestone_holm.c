#pragma strict_types
//-*-C++-*-
// file name:      /d/Avenir/common/bazaar/NPCS/jadestone.c
// creator(s):     Ilyian May 1995
// purpose:	   Jadestone is a member of the Hegemon's Honour Guard. 
//                 She is 'temporarily' in the service of the Inquisitor.
//                 Whether by disgrace or honour -- who knows?
//                 Large Npc, good weapons, some small quests
// note:           She wields /d/Avenir/common/bazaar/Obj/wield/shintor.c
//                 Her jdagger.c is also very poisonous.
// last update:    Lilith June 2022: After 27 years of service in the Bazaar
//                   Jadestone has been rewarded by the Hegemon with an 
//                   all-you-can-Hunt pass to the Holm. This file was copied 
//                   from the Bazaar, and the one in the bazaar is a modified
//                   version of the original Jadestone + dej minha, minus her
//                   special gear.

# include <composite.h>
# include <cmdparse.h>
# include <filter_funs.h>
# include <macros.h>
# include <money.h>;
# include <ss_types.h>
# include <language.h>
# include <stdproperties.h>
# include <wa_types.h>
# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/macros.h"
# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/smis/sys/statserv.h"
# include "/d/Avenir/include/guilds.h"
# include "/d/Avenir/include/relation.h"

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/lib/unique";

# define NHEALS        10 
# define KILL_FILE	"/d/Avenir/log/deaths/jadestone"
# define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))

/* Function prototypes */
string my_long();
string give_task();
string new_spot();

int been_attacked, last_start_fight = time(), last_hit, nheals;
object pouch, shintor, knife;

private static int heartbeat, counter;

void
reset_monster()
{
    ::reset_monster();

    nheals = NHEALS;
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    setuid();
    seteuid(getuid());

     set_name("jadestone");
     set_living_name("jadestone");
     set_name(({"jadestone Doll","jadestone doll","doll","elf","woman",
                "jadestone", "dej", "dej-minha"}));
     set_title("the High Mistress of the Black Flower");
     set_race_name("half-elf");
     set_adj("bare-breasted");
     add_adj("raven-haired");
     set_gender(G_FEMALE);
     set_alignment(0);
     set_appearance_offset(0);
     set_long(my_long);

     set_stats(({200, 200, 200, 100, 100, 100 }));
     set_knight_prestige(1100);    // 'cause she's so nasty...
	 
	 // Adding native armour - Lilith June 2022
     set_all_hitloc_unarmed(30);  
	 
     set_skill(SS_DEFENCE,      95);
     set_skill(SS_2H_COMBAT,   100);
     set_skill(SS_ACROBAT,     100);
     set_skill(SS_WEP_SWORD,   100);
     set_skill(SS_AWARENESS,    92);
     set_skill(SS_WEP_KNIFE,   100);
     set_skill(SS_BLIND_COMBAT, 80);
     set_skill(SS_PARRY, 85);

     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(NPC_I_NO_FEAR, 1);
     add_prop(NPC_I_NO_LOOKS, 1);
     add_prop(LIVE_I_SEE_INVIS, 1 + random(10));
     add_prop(CONT_I_HEIGHT, 210);
     add_prop(CONT_I_WEIGHT, 50000);
     add_prop(LIVE_M_ATTACK_THIEF, thief_fun);
     add_prop(LIVE_I_QUICKNESS, 125);
     add_prop(LIVE_I_SEE_INVIS, 50);

    set_exp_factor(175); /* because she is so hard to kill  */
    set_restrain_path(({"/d/Avenir/common/holm/", "/d/Avenir/common/park/"}));
    set_monster_home("/d/Avenir/common/holm/jungle/hf1");
    set_random_move(5 + random(25));	

  set_act_time(1);
      // This moves her to a new location in the Park or Holm dirs.
	  add_act(new_spot); 
      add_act("emote idly traces the tattoo on her chest while listening "+
          "intently for something.");
      add_act("emote tightens her grip on her dagger.");
      add_act("emote seems to consider you beneath notice.");
     	  
  set_cact_time(2);
      add_cact("swing shintor");
      add_cact("kiss shintor");
      add_cact("hold shintor");

    add_ask(({"bath", "melchior's bath"}),
        "say There is a bathhouse in the City. I'd like to "+
        "get there myself when I'm finished with my Hunt.",1);
    add_ask(({"sybarus","bazaar"}),
        "say You should go there. Now. Before you die here.",1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}), 
        "say Once I have fulfilled my bloodlust I will return to the City.",1);
    add_ask(({"infidel", "infidels"}),
        "say Not my monkeys, not my circus.",1);
    add_ask(({"infidel hideout", "hideout"}),
        "say Not my monkeys, not my circus",1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"punisher"}),"nod brief punisher",1);
    add_ask(({"lord high inquisitor", "inquisitor", "high inquisitor"}),
        VBFC_ME("inquis_ask"));
    add_ask(({"master", "Master"}), "say Whom I Serve is no business of yours.", 1);
    add_ask(({"jazur"}), VBFC_ME("jazur_ask"));
    add_ask(({"union","shadow union","shadow warrior"}), VBFC_ME("union_ask"));
    add_ask(({"past","history", "dej-minha"}), VBFC_ME("past_ask"));
    add_ask(({"mercenary air", "mercenary", "sellsword"}), VBFC_ME("merc_ask")); 
    add_ask(({"are you a mercenary"}), VBFC_ME("merc_ask")); 
    add_ask(({"galerin", "galerin icu ra'let"}),
        "say He is probably at Melchior's Bath House right now.", 1);
    add_ask("nochipa", "say She is an infidel priest of Alphum.", 1);

    set_default_answer(VBFC_ME("what_me"));

 
    /* No cheat-by-disarm to get her special weapons. */
    add_prop("_ranger_i_not_disarm", 100);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);	
	add_leftover("/d/Avenir/inherit/leftover", "trefoil tattoo",1, "", 0,0);
	
    add_item(({"chest", "breast", "tattoo", "trefoil tattoo", 
        "tattoo on dej-minha"}), "An irridescent ink has "+
        "been used to create a tattoo in the shape of a trefoil. It is "+
        "located on the upper-left side of her chest, over her heart.\n");
    add_item(({"hair", "braid", "braids", "twin braids", "hairstyle", 
        "hair on dej-minha", "hair on the dej-minha"}),
        "The hair on the sides of her head is braided close to the "+
        "scalp, directing the flow of hair down her back and out of "+
        "her way. This hairstyle is very attractive and enhances her "+
        "natural beauty.\n");
}

// This moves Jadestone around to various spots on the Island.
string 
new_spot()
{  
	command("emote suddenly tenses as she hears something, then "+
        "leaps into the vegetation nearby, disappearing from sight.");
    move_living("M", one_of_list(({
        HOLM +"jungle/hf1", HOLM +"jungle/hf5",
	    HOLM +"jungle/lf1", HOLM +"jungle/lf10", 
        HOLM +"shore/sh10", HOLM +"shore/sh20", 
        HOLM +"t_camp/c10", HOLM +"t_camp/c9",
	PK +"w_path4", PK +"s_path4", PK +"e_path9" })), 1, 1);    
	command("emote emerges from the underbrush nearby.");
    return "";	
}
	
void
equip_me()
{
     MONEY_MAKE_GC(random(25))->move(this_object());
     MONEY_MAKE_PC(1)->move(this_object());

     equip(({ 
        "/d/Avenir/common/obj/syb_coin",
        CITY +"obj/worn/filibeg",
        CITY +"obj/worn/harness",
        CITY +"obj/worn/stocking",
        BAZAAR+"Obj/worn/jboots",
        clone_unique(BAZAAR+"Obj/worn/jband", 20, 0, 0),
        BAZAAR+"Obj/worn/jcirclet",
        BAZAAR+"Obj/worn/jgloves",
        }));

     knife = clone_object(BAZAAR+"Obj/wield/jdagger");
     knife->move(this_object());
     knife->add_name("doll::dagger");

     command("wield doll::dagger");

     // NB: she does not wield the sword unless attacked.
     shintor = clone_unique(BAZAAR + "Obj/wield/shintor", 7,
	 HOLM + "obj/falchion_nm", 1, 25);
     shintor->move(this_object());
     shintor->add_name("doll::sword");
     shintor->shimmer(1);
     shintor->set_colour(-4);

     /* Fool the steal test. */
     if (shintor->id("fauxcwicseolfor"))
	 shintor->add_name("shintor");

     pouch = clone_object(BAZAAR+"Obj/misc/gem_pouch.c");
     pouch->move( this_object() );
     pouch->fill_pouch();
}

string
my_long()
{
    string  str;

    str = "She is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", female "+ query_race_name() +".\n";
    }

    str += "She has the physical grace characteristic of shadow elves, "+
         "with the sturdier build of a human, revealing her half-elven "+
         "heritage.\n"+
         "Her skin is so pale as to be translucent, its whiteness tinted "+
         "blue in some places by her veins.\n"+
         "Her long black hair, free of any constraint save twin braids "+
         "at her temples, brushes against her waist.\n"+
         "Her face is a perfect, pale oval, marred only by the cruel twist "+
         "of her full mouth.\n"+
         "Her dark green eyes have a predatory gleam.\n"+
         "She seems to glow with grace and power.\n"+	
         "She is without a shirt so you can see the glitter of a trefoil "+
         "tattoo over her heart.\n"+		 
         "";
    return str;
}


string
inquis_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say I served his interests at the Hegemon's behest. "+
       "The cost was high for me--27 years of my life--but I was "+
       "amply rewarded for my efforts.");
    command("emote smiles mirthlessly, with a look in her eyes "+
        "that sends a shiver down your spine.");
    return "";
}

string
merc_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
 
    command("say My days of serving the Lord Inquisitor at  "+
        "the Hegemon's behest are over now. I did not enjoy "+
        "pretending to be a sellsword.");
    command("say Now move along, before I decide to Hunt you.");
    return "";
}

string
union_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say It is a Union of Shadow Warriors, bound to serve "+
        "the Nobles of Sybarus and the interests of Jazur, their "+
        "Patron.");
    command("say The Union is where I would be today, had I not "+
        "been called to serve as dej-minha.");
    return "";
}

string
jazur_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say Jazur is a multi-faceted goddess. She is Goddess of "+
        "the Twelfth Hour, as well as the Patron of the Shadow Union "+
        "and The Dancers of Veils.");
    command("say She rules over Passion and all it touches, from sensu"+
        "ality to rage.");
    command("say I'm leaning toward bloodlust passion myself.");
    return "";
}

string
past_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say As a dej-minha I serve the Hegemon's interests. I served "+
       "long and well, and my reward is to Hunt to my heart's content.");
    command("say Should I hunt you, I wonder?");
    return "";
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }

    switch(random(5))
    {
        case 0:
        { 
            command("rolleyes");
            command("say You can't really be expecting me to answer that!");
            break;        
        }
        case 1:
        {
            command("say You must be inviting death, to pester me with "+
                "questions. Begone!");
            command("sneer");
            break;
        }
        case 2:
            command("emote laughs the chilling laugh of one who has "+
            "known total fear and is no longer afraid of anything.");
            break;
        case 3:
        {
            command("say I'd just as soon kill you as answer that!");
            command("grumble angrily");
            break;
        }
       case 4:
       {
           command("say Give me one good reason why I should answer "+
               "you.");
           command("smile slowly");
           break;
       }
    }
    return "";    
}

/* We prevent stealing here to avoid gimmick'ing props. */
public int
hook_victim_no_steal_bonus(object item)
{
    return 9999;
}

/* If by some miracle... */
public void
hook_victim_stolen_object(object item, object thief, object place)
{
    if (item->id("fauxcwicseolfor"))
	item->remove_name("shintor");
}

public void
thief_fun(object thief, object victim, object ob)
{
    been_attacked = 1;

    if (TP->query_prop(OBJ_I_INVIS))
    {
        set_alarm(1.5, 0.0, &command("say Alphum grants "+
				     "my deeper sight, scum."));
    }
    set_alarm(0.5, 0.0, &command("emote screams in rage!"));
    set_alarm(1.0, 0.0, &command("wield doll::dagger"));
    set_alarm(1.2, 0.0, &command("wield doll::sword"));
    set_alarm(1.5, 0.0, &command("kill " + OB_NAME(TP)));
}

string 
query_exp_title()
{
    return "sybarite";
}

public void
check_unwield(void)
{
    /* We are still fighting. */
    if (objectp(query_attack()))
    {
	/* Reset counter in case of new attack. */
	counter = 0;
	return;
    }

    /* Give a delay so we don't unwield between bounces. */
    if (++counter < 4)
	return;


    remove_alarm(heartbeat);
    counter = heartbeat = 0;
    command("unwield doll::sword");
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (!been_attacked)
    {
        been_attacked = 1;
        set_alarm (0.5, 0.0, "command", "emote whispers: Fool.");
        set_alarm (1.0, 0.0, "command", "emote draws " +
		   LANG_ASHORT(shintor) + ".");
        set_alarm (1.3, 0.0, "command", "wield doll::dagger");
        set_alarm (1.5, 0.0, "command", "wield doll::sword");
        set_alarm (1.8, 0.0, "command", "smile danger enemy");
        set_alarm (5.0, 0.0, "command", "kiss shintor");
    }

    if (!heartbeat)
	heartbeat = set_alarm(30.0, 30.0, check_unwield);
}

void
attack_object(object ob)
{
    ::attack_object(ob);

    if (!heartbeat)
	heartbeat = set_alarm(30.0, 30.0, check_unwield);
}

// make sure we unwield before we die or the room sees
//   the npc's unwield msg from Shintor.
void
do_die( object killer )
{
    object *foos = query_enemy(-1);
    string *killers;
    object poison;

    if (query_hp() > 0)
        return;

    if (!killer)
        killer = previous_object();

    /* do not die because of poison, players attempt this
     * to get around her poisoning death strike. */
    if (!living(killer))
    {
	heal_hp(50 + random(100));
	return;
    }

    foos -= ({ killer });
    killers = foos->query_name();

    SCROLLING_LOG(KILL_FILE, "Jadestone Doll "
            + "(" + (present("shintor") ? "with Shintor" : "without Shintor")
            + "): Killed by " + killer->query_name()
            + "(" + killer->query_average_stat()
            + ") " + (sizeof(killers) ? "with "
            + COMPOSITE_WORDS(killers) : "alone") + " [fight duration: "
            + ((time() - last_start_fight)/60)
            + " min]");

    command("wield doll::dagger");
    if (knife->query_wielded() == TO)
    {
        poison = clone_object(BAZAAR+"Obj/misc/j_poison");
        poison->move(killer, 1);  // Lets punish the killer a little bit...
        tell_room(ENV(killer), QCTNAME(TO) + " stabs at " + QTNAME(killer) +
                  " with her sinuous cinquedea one last time.\n", killer);
        killer->catch_msg(QCTNAME(TO)+" stabs at you with her " +
			  "sinuous cinquedea one last time.\n");
    	poison->start_poison();
    }

    command("unwield all");
    command("emote smiles bitterly.");
    STATSERV_LOG_EVENT("holm", "Killed Jadestone Doll");

    knife->remove_name("doll::dagger");
    shintor->remove_name("doll::sword");

    if (shintor->id("fauxcwicseolfor"))
	shintor->remove_name("shintor");

    ::do_die(killer);
}


/*
 *   Code relating to quests
 */
string
give_task()
{
    command("say There is nothing you can do for me that I cannot do "+
        "myself.");
    command("say Begone!");
	  return "";
}
/*
void
give_token(object player)
{
    object token;
    string str; 

    token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(player);
    str = token->short();
    player->catch_msg(QCTNAME(TO) + " gets a " + str + " from her "+
        "belt and gives it to you.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " gives a " 
        + str + " to " + QTNAME(player) + ".\n", ({ player }));
}
*/

void drop_unwanted(object what, object who)
{
    command("peer "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
        +who->query_real_name()))
        what->remove_object();  
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    set_alarm(0.1, 0.0, &drop_unwanted(obj, from));
}

static void tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

int special_attack(object enemy)
{
    object     me,
              *enemies;
    string     how;
    mixed     *hitres;
    int        damage, 
               swing_type, 
               pen,
               i, 
               con;
    string    *side = ({"left","right"}),
              *part = ({"knee","elbow","fist"}),
              *area = ({"stomach","chest","face"});

    // Cirion, Jan 2, 1998: Also log the amount of time
    // the fight lasted.
    if((last_hit + 500) < time())
        last_start_fight = time();

    last_hit = time();


    me = this_object();

    if (present(shintor))
    {
      shintor->shimmer(1);
      shintor->set_colour(-4);
    }

    command("wield doll::dagger");
    command("wield doll::sword");

    if(random(3))
      return 0;

    con = query_attack()->query_stat(SS_CON);

    enemies = query_enemy(-1);

    if(sizeof(enemies) > 1)
      for(i=0;i<sizeof(enemies);i++)
      {
         if(present(enemies[i], ENV(TO)) && enemies[i]->query_stat(SS_CON) < con)
         {
           attack_object(enemies[i]);
           con = enemies[i]->query_stat(SS_CON);
         }
      }

    enemy = query_attack();
    pen = random(1500) + 100 - enemy->query_skill(SS_DEFENCE);
    swing_type = random(3);
    hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);
    damage = hitres[0];

    how = "bumping";
    if (damage > 7)
        how = "grazing";
    if (damage > 12)         
        how = "hurting";
    if (damage > 25)
        how = "bashing";
    if (damage > 40)
        how = "smashing";
    if (damage > 60)
        how = "crushing";

    enemy->catch_msg(QCTNAME(me) + " swings her "
                  + side[random(2)] + " "
                  + part[swing_type] +" at you with great "
                 + "force, " + how + " your "
                  + area[swing_type]+".\n");
 
    /* Cirion: I am using query_combat_object()->tell_watcher(),   */
    /*         even through this should be define for livings. For */
    /*         some reason, it does not seem to be defined by her. */
    /*         I don't have time to fix it, so I will just patch   */
    /*         it.                                                 */
    query_combat_object()->tell_watcher(QCTNAME(me) + " swings her "
                  + side[random(2)] + " "
                  + part[swing_type] + " at "
                  + QTNAME(enemy) + " with great "
                  + "force, " + how
                  + " " + enemy->query_possessive()+ " "
                  + area[swing_type]+".\n", enemy);

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(15);

    if (!query_attack())
	been_attacked = 0;

    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(tp))
    {
        command("wield doll::dagger");
        command("wield doll::sword");
        command("kiss shintor");
        command("smile triumphantly");
        command("kill "+ OB_NAME(tp));
        command("shout Die, you Infidel scum!");
        return;
    }
    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 0)           
            command("say to "+ tp->query_real_name() +" Celebrate "+
                "the Source!");
        if (i == 2)
            command("greet "+ tp->query_real_name());
        if (i == 5)
            command("say to "+ tp->query_real_name() +" Still "+
                "preoccupied with serving Jazur, I see.");
        return;
    }
    else
    {
        if (i == 1)
           command("say Mascarvin's Paps! MORE Outlanders!");
        if (i == 5)
           command("say to "+ tp->query_real_name() +
               " I wonder which pitiful god you cry out to when you die.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (query_attack())
	return;

    if (CAN_SEE(TO, TP))
    {
        set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  

// Heals during combat.
void heal_me()
{
    heal_hp(1700); 	// about 1/3 of health
//    refresh_living(); 
    command("emote cries out: Lady Sachluph aid me in my "+
            "hour of need!");
    command("emote chews on a berry.");
    command("emote seems to be feeling much better.");
}

// Give her something that resembles an evade
int query_not_attack_me(object who, int aid)
{
    mixed comm;
	
	if (random(10) == 0)
    {
        --nheals;
        if (nheals >= 0)
          heal_me();
    }
    
	if (random(4) == 0)
	{
    who->catch_msg(QCTNAME(this_object()) +" dances lightly aside, "+
    "causing you to miss. How does she do that?!\n");       
    comm = (({"emote laughs with exuberance.",
    "say to "+ OB_NAME(who) +" Mascarvin will come for me when I die--"+
    "who will come for you?",
    "say to "+ OB_NAME(who) +" Surely you can do better than that?",
    "say to "+ OB_NAME(who) +" You're wasting my time.",
    "emote makes evading attacks look easy.",
    "say You almost gave me a haircut there!",
    "say to "+ OB_NAME(who) +" On the Holm, all is fair!",
    }));           
    command(one_of_list(comm));
    return 1;
	}
  	
	return 0;
}

/* Add some magical resistance to even the playing field */
varargs mixed 
query_magic_protection(string prop, object what)
{
    if (what == this_object())
    {
        if (prop == MAGIC_I_RES_MAGIC)
        {
            tell_room(ENV(TO), QCTNAME(TO)+"'s spiral tattoo pulses "+
                "with irridescent light.\n", what);
            return ({ 25, 1});
        }
        if (prop == MAGIC_I_RES_POISON)
        {
            tell_room(ENV(TO), QCTNAME(TO)+"'s spiral tattoo pulses "+
                "with irridescent light.\n", what);
            return ({ 25, 1});
        }

    }
 
    return ::query_magic_protection(prop, what);
}

/* Stop knights from cheating with mercy. */
public int
query_disallow_mercy(void)
{
    return 1;
}
