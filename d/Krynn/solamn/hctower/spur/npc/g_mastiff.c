// grace apr 1995

inherit "/d/Krynn/open/monster/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../local.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3

#define H_HEAD 0
#define H_BODY 1
#define H_LFQ  3
#define H_RHQ  4

string randsize();
string randtnt();

string size=randsize();
string tnt=randtnt();

void
create_creature()
{
    set_name("mastiff");
    set_pname("mastiffs");
    add_name("dog");
    set_race_name("mastiff");
    set_adj(size);
    add_adj(tnt);
    set_short("@@short_desc");
    set_long("@@long_desc");

/*              str, con, dex, int, wis, dis           */
    set_stats(({ 70,  90,  90, 100, 100,  70}));

    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 40);

    set_alignment(10);
    set_knight_prestige(-1);
    set_aggressive("@@do_align_check@@");  // will attack if align < -200
    add_prop(LIVE_O_ENEMY_CLING, 1);


    set_cact_time(2);
        add_cact("emote bares its teeth in a menacing growl.");

    set_act_time(10);
        add_act("emote pads restlessly about.");
        add_act("emote licks its chops and yawns widely.");
        add_act("@@rub");

    set_attack_unarmed(A_BITE,   15, 15,   W_IMPALE,  20, "jaws");
    set_attack_unarmed(A_LCLAW,  10,  10,    W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW,  10,  10,    W_SLASH,  10, "right paw");
    set_attack_unarmed(A_TAIL,   10, 10, W_BLUDGEON,  10, "tail");

    set_hitloc_unarmed(H_HEAD, ({ 70 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 90 }), 50, "body");
    set_hitloc_unarmed(H_LFQ,  ({ 70 }), 20, "left foreleg");
    set_hitloc_unarmed(H_RHQ,  ({ 70 }), 20, "right hind-quarter");

    add_prop(LIVE_I_SEE_DARK, 40);
    add_prop(NPC_I_NO_LOOKS, 1);

   ::create_creature();
}


/* ***********************************************************
   These react sequences are borrowed from Olorin's Pharazon
   ********************************************************* */    
void
init_living()
{
    object  tp = TP;

    ::init_living();

    if (!interactive(tp))
        return;

    set_alarm(3.0, 0.0, "react_meet", tp);
}  


void
react_meet(object tp)
{
    string  occ,
            name = tp->query_real_name();

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();

    switch(occ)
    {
        case "Solamnian Knights":
            command("emote wags its tail happily.");
            command("lick " +tp->query_real_name());
            break;
        case "Gondorian Rangers Guild":
            command("emote sniffs you cautiously.");
            command("emote gives your hand a tentative lick.");
            break;
        case "Shield and Club Warriors":
            command("growl "+tp->query_real_name());
            command("emote looks like it is going to bite you.");
            break;
        case "Calian warrior's guild":
            command("emote circles around you.");
            command("emote seems to accept your presence.");
            break;
        case "Ancient Kaheda Order":
            if (tp->query_alignment() < 10)
            command("snarl "+tp->query_real_name());
            command("bite "+tp->query_real_name());
            break;
        default:
            if ((!tp->query_met(query_real_name())) && 
                (tp->query_alignment() < 0))
                command("snarl "+tp->query_real_name());
            break;
    }
}


int
do_align_check()
{
    if (TP->query_npc())
       return 0;
    if (TP->query_alignment() > -200)
       return 0;
    if (TP->query_average_stat() < 30)
       return 0;
    else
      set_alarm(1.0,0.0,"command","snarl");
    return 1;
}    
int
query_knight_prestige() { return -1; }

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{

   if (aid == A_BITE)
   {
       tell_object(enemy, "The mastiff sinks its jaws into you!\n");
   }

   if (aid == A_TAIL)
   {
       tell_object(enemy, "The mastiff's tail whips around "+
                "and strikes you with such force that you "+
                "are momentarily frozen in pain!\n");
       enemy->add_attack_delay(2);
   }

   return 0;
}

string
randtnt()
{
   string str;

   switch(random(7))
   {   
      case 0: str="brown";    break;
      case 1: str="black";   break;
      case 2: str="red";     break;
      case 3: str="yellow";  break;
      case 4: str="gray";    break;
      case 5: str="brindle";   break;
      case 6: str="white";   break;
   }
   return str;                                                                               
}

string
randsize()
{
   string str;

   switch(random(5))
   {   
      case 0: str="tiny";        break;
      case 1: str="small";       break;
      case 2: str="fierce";   break;
      case 3: str="large";  break;
      case 4: str="huge";        break;
   }
   return str;                                                                               
}

string
short_desc()
{
   return ""+size+ " " +tnt+ " mastiff";
}

string
long_desc()
{
    return "This mastiff has a "+ tnt +"-coloured, short-haired "+
"coat. It is " +size+ " in size, and very powerfully "+ 
           "built. It looks like it could do some damage if pro"+
           "voked.\n";
}

/*
* Function name: notify_ob_attacked_me
   * Description:   This is called when someone attacks a team member of mine
* Arguments:     friend - My team mate
*                attacker - The attacker
*/
void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;

   if (random(10))
     set_alarm(itof(random(5)),0.0,"help_friend", attacker);
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
      {
          command("kill " + ob->query_real_name());
      }
}                      

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
    int i = check_call(monster_aggressive);
    if ((!i) || (this_player()->query_npc()))
        return;

    if (do_align_check() &&
       (monster_attack_chance == 0) || (random(100) < monster_attack_chance))
      set_alarm(2.0,0.0,"aggressive_attack", this_player());
}            


/*
* Function name: attacked_by
* Description:   This function is called when somebody attacks this object
* Arguments:     ob - The attacker
*/
void
attacked_by(object ob)
{
   object *arr;
   int i;

   ::attacked_by(ob);

   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->notify_ob_attacked_me(this_object(), ob);
}          





