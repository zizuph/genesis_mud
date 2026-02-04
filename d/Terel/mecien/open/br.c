/*
 * /d/Gondor/common/npc/blackrider.c
 * 
 * One of the nastiest dangers to be met in Gondor.
 * Killable only with Undead-slaying magical weapons.
 * By Elessar, Gondor, Genesis - 5. Nov. 1992.
 * changed black breath from add_cact to special_attack, Olorin, 19-sep-1993
 * special_attack() modifed to use resolve_task(), Olorin, 2-nov-1993
 * added resistance against magic,
 * reduced effectiveness of special attacks on nazgul,
 * added alignment bonus for hits on nazgul.
 * Olorin, 12-nov-1993
 * Increased Nazgul stats to 160 for str, dex and con
 * Increased magic resistance, except lowering it for fire, as from
 * the books...  Dunstable March 20, 1994
 */
inherit "/std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/evilkill.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_titles.h"

#define CEX if (!combat_extern) combat_reload()
#define NPC_LOG               (LOG_DIR + "npcs")
#define BLACK_BREATH_FQ_1     100   /* random(FQ_1) < FQ_2 ==> special attack  */
#define BLACK_BREATH_FQ_2      25   /* ie with FQ_1 = 100, FQ_2 = 40 ==> 40%   */
#define NAZGUL_SKILLS         ({TS_DEX, SS_SPELLCRAFT, SS_FORM_CONJURATION, SS_ELEMENT_DEATH})
#define PLAYER_SKILLS         ({TS_DEX, SS_SPELLCRAFT, SS_FORM_ABJURATION,  SS_ELEMENT_LIFE})

int     hooded,
        riding,
        spell_broken;
object  last_weapon;

void
create_monster()
{
   set_name("wraith");
   set_living_name("nazgul");
   add_name(({"nazgul", "man", "shape", "figure", "rider", "ringwraith", "shadow"}));
   set_adj(({"dark-skinned", "black-robed", "red-eyed", }));
   set_short("@@short_func");
   set_long("@@long_func");
   set_stats(({ 220+random(10), 200+random(10), 200+random(10), 
            145+random(10),  135+random(10), 160+random(10) }));
   set_learn_pref(({1,1,1,0,0,0,}));
   set_base_stat(SS_OCCUP, query_average_stat() + random(10) -5);
   add_subloc(MORGUL_S_SUBLOC, TO);
   set_alignment(-900);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_2H_COMBAT,90);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_KNIFE,50);
   set_skill(SS_PARRY,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,100);
   set_skill(SS_FORM_ENCHANTMENT,60);
   set_skill(SS_FORM_CONJURATION,100);
   set_skill(SS_FORM_ABJURATION,60);
   set_skill(SS_FORM_ILLUSION,40);
   set_skill(SS_FORM_TRANSMUTATION,40);
   set_skill(SS_FORM_DIVINATION,20);
   set_skill(SS_ELEMENT_DEATH,100);
   set_skill(SS_ELEMENT_AIR,60);
   set_skill(SS_ELEMENT_FIRE,60);
   set_skill(SS_ELEMENT_LIFE,40);
   set_skill(SS_ELEMENT_EARTH,60);
   set_skill(SS_ELEMENT_WATER,60);
   
   add_prop(CONT_I_HEIGHT,193);
   add_prop(CONT_I_WEIGHT,98000);
   add_prop(NPC_I_NO_LOOKS,1);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_SEE_INVIS,100);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_UNDEAD, 100);
   add_prop(LIVE_I_NO_CORPSE,1);
   
   add_prop(OBJ_I_RES_MAGIC,70);
   add_prop(OBJ_I_RES_DEATH,70);
   add_prop(OBJ_I_RES_LIFE,70);
   add_prop(OBJ_I_RES_LIGHT,70);
   add_prop(OBJ_I_RES_WATER,20);
   add_prop(OBJ_I_RES_AIR,70);
   add_prop(OBJ_I_RES_EARTH,40);
   add_prop(OBJ_I_RES_FIRE,20);
   add_prop(OBJ_I_RES_COLD,60);
   add_prop(OBJ_I_RES_POISON,100);
   add_prop(OBJ_I_RES_ELECTRICITY,30);
   
   add_item("horse","@@exa_horse");
   add_item("beast","@@exa_beast");
   riding = 1;
   hooded = 1;

   set_act_time(5);
   add_act("@@hiss");
   add_act("battlesong");
   add_act("gaze");
   add_act("leer");
   add_act("mlaugh");
   add_act("mordor");
   add_act("mremember");
   add_act("mscoff");
   add_act("msmile");
   add_act("msniff");
   add_act("torture");

   set_cact_time(1);
   add_cact("@@hiss");
   add_cact("mcurse");
   add_cact("shriek");
   add_cact("@@emote_enemy|damn@@");
   add_cact("@@emote_enemy|mcurse@@");
   add_cact("@@emote_enemy|mscoff@@");
   add_cact("@@emote_enemy|sneer@@");
   add_cact("@@emote_enemy|torture@@");
   add_cact("@@emote_enemy|wrath@@");
   add_cact("wail");

   seq_new("do_things");
   seq_addfirst("do_things","@@arm_me");
}

void
set_beast_type(int i)
{
    /* 0 = On foot, 1 = Black Horse, 2 = Fell Beast */
    if (i < 0)
        riding = 0;
    else if (i > 2)
        riding = 2;
    else
        riding = i;
}

string
random_hiss()
{
   switch(random(5))
   {
      case 0: return "";
      case 1: return "I seek Bagginss!";
      case 2: return "Bagginsss is not in the Shire anymore!";
      case 3: return "Bagginsss has sssomething I want!";
      case 4: return "I will reward you well if you tell me where Bagginsss isss!";
      default: return "";
   }
}

void
hiss(string str)
{
   if (strlen(str)) 
      tell_room(ENV(TO),"The black rider hisses: "+str+"\n",TO);
   else 
      hiss(random_hiss());
}

void
arm_me()
{
   object obj;
   seteuid(getuid(TO));
   obj = clone_object(WEP_DIR + "nazgul_sword");
   obj->move(TO);
   command("wield sword");
   obj = clone_object(MAGES_DIR + "npc/npc_robe");
   obj->check_spell_object(TO);
   obj->move(TO);
   add_cmdsoul(MORGUL_SOUL_FILE);
   update_hooks();
   command("wear robe");
   obj = clone_object(ARM_DIR + "nazgul_plate");
   obj->move(TO);
   command("wear plate");
   obj = clone_object(ARM_DIR + "nazgul_helm");
   obj->move(TO);
   command("wear helm");
   hiss("Have you seen Bagginssss?");
}

void
fear(int panic, object who)
{
    if (IS_MORGUL_MAGE(who))
        return;

   tell_object(who,BSN("You feel fear creeping upon you as you look at the dark, menacing "+
         "figure, and you struggle to control yourself! "));
   who->add_panic(panic + MAX(0, (1000 - ABS(who->query_alignment())) / 10 ));
}

void
test_presence()
{
   if (CAN_SEE(TO,TP) &&
         (TO->query_skill(SS_AWARENESS) > TP->query_skill(SS_HIDE)))
   tell_object(TP,"You feel that the black shape is staring straight at you.\n");
}

void
init_living()
{
   ::init_living();
   fear(60,TP);
   test_presence();
}

/*
 * Function name: init_attack
 * Description:   Called from init_living()
 */
public void
init_attack()
{
    if ((!monster_aggressive) || (TP->query_npc()) || (query_friend_or_foe(TP) < 1))
        return;

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
        set_alarm(2.0, 0.0, &aggressive_attack(TP));
}

string
short_func()
{
   if (riding == 1)
      return "large black-cloaked shape riding a black horse";
   else if (riding == 2)
      return "large black-cloaked shape riding a fell winged beast";
   else
      return "large black-cloaked, hooded man on foot";
}

string
mount_desc(int i)
{
   if (i == 0) return "is walking on foot.";
   if (i == 1) return "is riding a large black horse.";
   if (i == 2) return "is riding a fell winged beast.";
}

string
long_func()
{
   if (TP->query_prop(LIVE_I_SEE_INVIS))
   {
      return BSN("The tall, dark shape now stands terribly clear before you. In "+
         "his white face burns keen and merciless eyes; under his mantle is a "+
         "long grey robe; upon his grey hairs a helm of silver, and sword of "+
         "steel in his haggard hand. The threatening man "+mount_desc(riding));
   }
   if (hooded)
   {
      return BSN("The black shape looks like a man, wrapped in a great black cloak "+
         "and hood, so that only his boots showed below, his face shadowed and "+
         "invisible, save a deadly gleam of eyes. The threatening shape "+
         mount_desc(riding));
   }
   return BSN("The black shape looks like a man, wrapped in a great black cloak, "+
      "his hood flung back. A helm of silver he wears, but between helm and "+
      "robe there is nothing to see, save only a deadly gleam of eyes! This is "+
      "a Nazgul, one of Saurons most deadly servants. The wraith "+
      mount_desc(riding));
}

string
exa_horse()
{
   if (riding == 1) 
      return BSN("The horse is black as night, and one of the largest you have seen. "+
         "Its eyes gleam with a maddening red light, as if controlled "+
         "by some terrifying evil.");
   return "";
}

string
exa_beast()
{
   if (riding == 2) 
      return BSN("The huge fell beast is a terrifying image to look upon! "+
         "Large bony featherless wings stretch out several meters to both "+
         "sides, and on the end of a long hideous neck sits a scary head "+
         "as from a creature of ancient times, with a long beak and eyes "+
         "gleaming with malice. The creature flaps its wings, and gives "+
         "a wailing high-pitched screech filling you with terror!");
   return "";
}

int
break_weapon(object weapon, object att)
{
   if (!att || !weapon) 
      return 0;
   tell_object(att,BSN("Your "+weapon->query_name()+
      " breaks in many shards as it hits the menacing shape!"));
   tell_room(ENV(TO), QCTNAME(att) + "'s " + check_call(weapon->short()) +
      " breaks into many shards as it hits the menacing shape!\n",att);
   weapon->add_prop(OBJ_I_BROKEN,1);
   set_this_player(att);
    att->unwield(weapon);
   weapon->unwield_me();
   command("cackle");
   hiss("No living man may hinder me, thou fool!");
   return 1;
}

int
query_not_attack_me(object att, int att_id)
{
   object  weapon = att->query_weapon(att_id);
   mixed  *mag_arr;
   int     mid;
   
   if (!weapon) 
      return 1;
   last_weapon = weapon;
   if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
   {
      if (!random(10))
         tell_room(ENV(TO),QCTNAME(att)+"'s "+weapon->query_name()
           + " seems to have no effect against the wraith!\n",att);
      else 
         break_weapon(weapon,att);
      return 1;
   }
   mag_arr = weapon->query_prop(MAGIC_AM_MAGIC);
/* added this to find source of runtime errors, Olorin, 04-may-1995 */
    if (!pointerp(mag_arr))
    {
        tell_room(ENV(TO), "The "+weapon->query_name()
          + " is broken. Please make a bug report!\n");
        log_file("npcs", file_name(weapon) + " has MAGIC_AM_MAGIC prop set "
          + " to an illegal value!\n");
    }
   if ((mid = member_array("undead-slaying",mag_arr)) > 0)
   {
      if (random(mag_arr[mid-1]) == 0)
         break_weapon(weapon,att);
      return 0;
   }
   if ((mid = member_array("enchantment",mag_arr)) > -1) 
   {
      if (random(mag_arr[mid-1]) < 5)
         break_weapon(weapon,att);
      return 0;
   }
   tell_room(ENV(TO), BSN("The magic in the " + check_call(weapon->short()) +
         " seems to have no effect on the wraith."));
   hiss("Your pitiful " + check_call(weapon->short()) + " does not worry me, mortal!");
   if(random(mag_arr[sizeof(mag_arr)-2]) < 10)
      break_weapon(weapon,att);
   return 1;
}

int
do_die(object killer)
{
   if (query_hp() > 0) 
      return 0;
   if (!killer)
      killer = previous_object();
   tell_object(killer,"You swing your weapon in between helm and mantle of the Nazgul.\n");
   tell_room(ENV(TO),BS(QCTNAME(killer)+" swings "+killer->query_possessive()+
         " weapon between helm and mantle of the dark figure.\n"),killer);
   tell_room(ENV(TO), BS("The helm rolls to the ground with a clang, and behold! " +
         "The mantle and hauberk are empty, and fall shapeless to the ground, torn " +
         "and tumbled!\n") + BS("A cry goes up into the shuddering air, fading to a " +
         "wailing passing with the wind, a voice, bodyless and thin, dies out.\n"));
   CEX; combat_extern->cb_death_occured(killer);
   killer->notify_you_killed_me(TO);
   write_file(NPC_LOG,"Black Rider: Killed by "+killer->query_name()+" ("+killer->query_average_stat()
     + ") on "+ctime(time())+".\n");
  if (objectp(last_weapon))
   write_file(NPC_LOG," - possibly killed with "+last_weapon->short()+" - "
     + MASTER_OB(last_weapon)+".\n");
   move_all_to(ENV(TO));
   TO->remove_object();
   return 1;
}

varargs string
black_breath(object victim)
{
   object breath;
   if(!victim)
      victim = TO->query_attack();
   
   if(!victim) return "";
   
   if (ENV(TO) == ENV(victim))
   {
      victim->catch_msg(QCTNAME(TO)+" hisses a cold, dark breath at you!\n"+
         "A dreadful chill runs down your spine!\n");
      tell_room(ENV(TO),QCTNAME(TO)+" hisses at "+QTNAME(victim)+" coldly.\n",victim);
      seteuid(getuid(TO));
      breath = clone_object(POISON_DIR + "black_breath");
      breath->move(victim);
      breath->start_poison();
      write_file(LOG_DIR+"curses",victim->query_name()+
         " poisoned with Black Breath by a Nazgul, "+ctime(time())+".\n");
      return "";
   }
   return "";
}

/* Solamnian Knights are honoured by this kill. */
int query_knight_prestige() { return 2500; }

int filter_enemy(object x)        { return (x->query_attack() == TO); }

int
special_attack(object enemy)
{
   object  *victim = ({});
   int      i,
   task;
   
   add_prop(LIVE_O_ENEMY_CLING, enemy);
   
    victim = filter(all_inventory(ENV(TO)), filter_enemy);
   
   if(sizeof(query_weapon(-1)))
   {
      if(random(BLACK_BREATH_FQ_1) >= BLACK_BREATH_FQ_2)
         return 0;
      task = TASK_DIFFICULT;
      task = TASK_ROUTINE;
      task = (TASK_DIFFICULT + TASK_ROUTINE) /2;
      if(!random(3))
         victim = ({enemy});
      else
         if(!objectp(victim))
             return 1;
         victim = ({ victim[random(sizeof(victim))] });
   }
   else
      {
      task = TASK_ROUTINE;
      task = TASK_SIMPLE;
      task = (TASK_SIMPLE + TASK_ROUTINE) /2;
   }
   
   while(i < sizeof(victim))
   {
      if(victim[i]->resolve_task(task, PLAYER_SKILLS, TO, NAZGUL_SKILLS) > 0)
         {
         if (ENV(TO) == ENV(victim[i]))
            {
            victim[i]->catch_msg(QCTNAME(TO)+" hisses a cold, dark breath at you!\n");
            tell_room(ENV(TO),QCTNAME(TO)+" hisses at "+QTNAME(victim[i])+" coldly.\n",victim[i]);
            fear(50,victim[i]);
         }
         }
      else
         black_breath(victim[i]);
      i++;
   }
   return 1;
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
   mixed result;
   int     dam,
   ap;
   
   if(attack_id == -1 && dt != MAGIC_DT)
      result = ::hit_me(wcpen/20, dt, attacker, attack_id);
    else if (attack_id == 0 && dt != MAGIC_DT)
        result = ::hit_me(wcpen/20, dt, attacker, attack_id);
    else
      result = ::hit_me(wcpen, dt, attacker, attack_id);
   
   if(result[3] > 0)
   {
      ap = attacker->query_alignment();
      dam = result[3] * MAX(0, 500 - ap);
      attacker->set_alignment(ap + dam/1500);
   }
   return result;
}

/*
 * These functions taken from:
 * /d/Gondor/common/guild2/morgul_shadow.c
 *
 * The guild shadow for the Morgul Mages of Gondor
 */

#define GUILD_TAX             25

int     query_guild_tax_occ() { return GUILD_TAX; }

string  query_guild_style_occ() { return GUILD_STYLE; }

string  query_guild_name_occ() { return GUILD_NAME; }

int     query_nazgul() { return 1; }

int     query_morgul_penalty() { return 1; }

int
query_morgul_level()
{
    int     m_stat = query_stat(SS_OCCUP),
            mlevel,
            nlevels = sizeof(MORGUL_AS_MALE_TITLES);

    if (m_stat > 100)
        m_stat = 100;

    mlevel = ((m_stat * (nlevels - 1)) / 100);
    mlevel -= query_morgul_penalty();
    if (mlevel < 0)
        mlevel = 0;
    mlevel += (query_nazgul() * nlevels);
    return mlevel;
}

string
query_morgul_title()
{
    if (query_nazgul())
    {
        if (query_gender() == 1)
            return MORGUL_AS_FEMALE_NAZGUL_TITLES[query_nazgul()-1];
        else
            return MORGUL_AS_MALE_NAZGUL_TITLES[query_nazgul()-1];
    }

    if (query_gender() == 1)
        return MORGUL_AS_FEMALE_TITLES[query_morgul_level()];
    return MORGUL_AS_MALE_TITLES[query_morgul_level()];
}

string  query_guild_title_occ() { return query_morgul_title(); } 

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int    hs,
           hl,
           mmp;
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_SUBLOC)
        return show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";

    switch(query_nazgul())
    {
        case 1:
            str += "one of the Nazgul of the Society of Morgul Mages.\n";
            break;
        case 2:
            str += "the Lord of the Nazgul, King of Minas Morgul.\n";
            break;
        case 0:
        default:
            str += "a Member of the Society of Morgul Mages.\n";
            break;
    }

    return str;
}

void
loot_corpse()
{
    command("get all from corpse");
    command("spit");
    command("think how the corpse isn't even worth scavenging for food.");
}

string
emote_enemy(string str)
{
    object  pl;

    if (!objectp(pl = query_attack()))
        return "";

    command(str+" "+pl->query_real_name());

    return "";
}

/*
 * Function name: move_living
 * Description:  redefinition to prevent teleports due to LIVE_O_ENEMY_CLING
 */

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    if (!objectp(query_prop(LIVE_O_ENEMY_CLING)))
        return ::move_living(how, to_dest, dont_follow, no_glance);

    if (!stringp(to_dest))
        to_dest = file_name(to_dest);

    if (member_array(to_dest, ENV(TO)->query_exit_rooms()) > -1)
        return ::move_living(how, to_dest, dont_follow, no_glance);

    log_file("npcs", "MOVE ERROR: Tried to move from "+file_name(ENV(TO))
      + " to " + to_dest + ", following "+query_prop(LIVE_O_ENEMY_CLING)->query_name()
      + " at " + ctime(time()) + ".\n");

    return 7;
}


