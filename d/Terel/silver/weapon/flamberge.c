/*
  
  by Pasqua & Udana, /2006


  Updated by Arman, providing some balancing of the magic-breaking
  aspect as well as taking into account the revised mana maximum
  of players.  June 2019
*/

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
//#include "../include/defs.h"
#include "/d/Terel/silver/include/defs.h"
/* used to calculate weight and volume*/
#define WEIGHT_MOD 2.5
/* used to calculate value */
#define VALUE_MOD 10.0
#define HIT 55
#define PEN 50
#define MAGIC_STRENGTH 45

#ifndef E
#define E(x) environment(x)
#endif

object sword_shadow;

create_weapon()
{
    set_name("flamberge");  
    add_name("sword");
    set_adj("gleaming");
    add_adj("black");
    set_short("gleaming black flamberge");   
    set_long("This formidable two-handed functional flamberge is " +
        "handcrafted with a sixty-inch blade that has been tempered " +
        "and hardened in flame by a true master smith. The wavy, " +
        "flame-like black blade is sharp enough to cut through anything " +
        "with ease and its wielder will strike fear into the hearts of " +
        "even the bravest enemies. The majestic, yet magical aura " +
        "surrounding this sword gives the impression that it has been " +
        "enchanted by a powerful being. The grip of this sword is " +
        "definitely not for the faint of heart with hand-cast fittings " +
        "of solid brass and exotic ebony handle.\n");
    set_default_weapon(HIT, PEN, W_SWORD,W_IMPALE | W_SLASH, W_BOTH);
  
    add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
    add_prop(OBJ_I_WEIGHT,
        ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)) * WEIGHT_MOD));
    add_prop(OBJ_I_VOLUME,
        ftoi(itof(query_prop(OBJ_I_WEIGHT)) / WEIGHT_MOD));

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({MAGIC_STRENGTH, "enchantment"}));
        
    add_prop(MAGIC_AM_ID_INFO, ({"It's a legendary blade of Aki'rin the " +
        "Mad - a Valkyrie who battled the Evil One's servants. The tales " +
        "say that this sword assured her a great victory over her enemies, " +
        "but at great cost. She no longer recognized her friends or " +
        "family, and eventually abandoned everything she ever loved... and " +
        "disappeared.\n", 15,
        "This sword has appeared in many similar legends throughout time, " +
        "with similar disastrous endings. A great hero enlists its aid to " +
        "great success, but ultimately turns mad or worse...\n", 25,
        "This sword identifies magic with the Evil One, and may destroy " +
        "items on the wielders person that radiate anything but the " +
        "strongest of magical auras.\n", 35, "In combat a hit by this " +
        "blade can blast an enemy's mind, affecting their memory of " +
        "friends and foe, or break their magical items.\n", 40}));
    add_prop(OBJ_S_WIZINFO, "This sword drains mana and reduces wisdom " +
        "upon wielding it. It no longer makes the wielder forget one " +
        "random name and no longer breaks all magical items he possess " +
        "with AM_MAGIC below AM_MAGIC of this item. On hit it can make " +
        "the enemy forget a name, drain its mana, or break its magical " +
        "item(s).\n");
    set_wf(TO);

}


int weaker_magic(object ob)
{
    if(pointerp(ob->query_prop(MAGIC_AM_MAGIC)))
    {
        //  If imbued it resists 
        if(ob->has_imbue_shadow())
            return 0;

        if(ob->query_prop(MAGIC_AM_MAGIC)[0] < random(MAGIC_STRENGTH))
            if(ob->query_magic_res(MAGIC_I_RES_MAGIC) < MAGIC_STRENGTH)
                if(ob->query_magic_res(OBJ_I_RES_MAGIC) < MAGIC_STRENGTH)
                    if(ob->query_prop(OBJ_M_NO_DROP) == 0)
                        return 1;
    }

    return 0;
}

void destroy_weaker_magic()
{
    if (!(TP))
        return;
    object *other_magic = filter(all_inventory(TP), &weaker_magic());
    for(int i = 0; i < sizeof(other_magic); ++i)
    {
        if(!stringp(other_magic[i]->query_auto_load()) &&
           !other_magic[i]->query_prop(OBJ_I_BROKEN))
        {
            int ver = objectp(other_magic[i]->query_worn()) +
                      objectp(other_magic[i]->query_wielded());
            other_magic[i]->add_prop(OBJ_I_BROKEN);
            other_magic[i]->remove_broken();
            if(!ver)
            {
                if(stringp(other_magic[i]->query_short()))
                    write("The " + other_magic[i]->query_short() +
                          " breaks!\n");
                else
                    write("The " + other_magic[i]->query_name() +
                          " breaks!\n");
            }
        }
    }
}

void give_back_skill(object victim, int level, int skill)
{
    victim->set_skill_extra(skill, level * (-1));
}

void forget_one(object victim, int phurt)
{
    int *possible_skills = filter(victim->query_all_skill_types(),
                                  &operator(<)( , SS_MAX));
    if(!sizeof(possible_skills))
        return;
    int skill = possible_skills[random(sizeof(possible_skills))];
    
    int level = random(phurt/2);
    if(level > victim->query_skill(skill) + victim->query_skill_extra(skill))
        level = victim->query_skill(skill) + victim->query_skill_extra(skill);
    level = level * (-1);
    victim->set_skill_extra(skill, level);
    set_alarm(60.0 + (rnd() * 60.0), 0.0,
              &give_back_skill(victim, level, skill));
}
    
    
mixed 
wield(object weapon)
{
    FIX_EUID;
    sword_shadow = clone_object(WEAPON + "sword_shadow");

    if(TP->query_mana() < 200)
    {
        TP->heal_hp(-500);
        TP->set_mana(0);
        say(QCTNAME(TP) + " starts to scream and falls to the ground with " +
            "blood dripping from " + TP->query_possessive() +
            " eyes, ears, and nose.\n");
        return "You scream as you fall to the ground and feel something " +
            "pouring out of your eyes, ears, and nose - it's blood!\n";
        if(TP->query_hp() <= 0)
            TP->do_die();
    }
    TP->add_mana(-200);
    sword_shadow->shadow_me(TP);
//  destroy_weaker_magic();
    say(QCTNAME(TP) + " successfully wields the " + TO->query_short() +
        " but seems to be drained by the effort.\n");
    TP->catch_msg("You strongly grip the ebony handle of the " +
        TO->query_short() + " as you successfully wield it in your hands. " +
        "However, you feel drained by the dark powers of the sword.\n");
    return 1;
}

public int 
unwield()
{
    sword_shadow->remove_shadow();
    write("Suddenly your life flashes before your eyes, and a cloud is " +
        "lifted from your memory.\n");
    return 0;
}

public varargs int did_hit(int aid, string hdesc, int phurt, object enemy,
                           int dt, int phit, int dam, int hid)
{
    string to_me, to_enemy, to_onlooker;
    object enemy_armour = enemy->query_armour(hid);
    object enemy_weapon = 
        (sizeof(enemy->query_weapon(-1)) ? enemy->query_weapon(-1)[0] : 0);
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    /*special attack*/
    if (aid == -1 || !objectp(enemy))
        return 0;
    
    
    /* Weapon does no special things unless phurt is above >10 */
    if(phurt > 10)
    {
        /* if someone found new magic item */
        if(!random(5))
            destroy_weaker_magic();
        
        /* forget name */
        if(hid == A_HEAD)
        {
            forget_one(enemy, phurt);
            enemy->catch_msg("The " + TO->query_short() + " connects with " +
                "your temple and you feel a tremendous pain followed by a " +
                "loss of memory as the wavy blade emits a blast of energy.\n");
        }
        /* drain mana */
        if(phit > 30 && hid != A_HEAD)
        {
            enemy->add_mana(- phurt / 2);
            enemy->catch_msg("The " + TO->query_short() + " connects with " +
                "your temple and you feel mentally drained as the wavy " +
                "blade saps your energy.\n");
        }
        /* destroy magic armour */
        if(objectp(enemy_armour) && phit > 35)
        {
            if(pointerp(enemy_armour->query_prop(MAGIC_AM_MAGIC)) &&
               enemy_armour->query_prop(MAGIC_AM_MAGIC)[0] < random(MAGIC_STRENGTH) &&
               enemy_armour->query_magic_res(MAGIC_I_RES_MAGIC) < MAGIC_STRENGTH  &&
               enemy_armour->query_magic_res(OBJ_I_RES_MAGIC) < MAGIC_STRENGTH  &&
               enemy_armour->query_prop(OBJ_M_NO_DROP) ==0)
            {
                enemy_armour->add_prop(OBJ_I_BROKEN);
                enemy_armour->remove_broken();
            }
        }
        if(phit > 50 && phurt > 40 && enemy_weapon)
        {
            if(pointerp(enemy_weapon->query_prop(MAGIC_AM_MAGIC)) &&
               enemy_weapon->query_prop(MAGIC_AM_MAGIC)[0] < random(MAGIC_STRENGTH) &&
               enemy_weapon->query_magic_res(MAGIC_I_RES_MAGIC) < MAGIC_STRENGTH  &&
               enemy_weapon->query_magic_res(OBJ_I_RES_MAGIC) < MAGIC_STRENGTH  &&
               enemy_weapon->query_prop(OBJ_M_NO_DROP) ==0)
            {
                enemy_weapon->add_prop(OBJ_I_BROKEN);
                enemy_weapon->remove_broken();
            }
        }
    }       

    /* chance for normal descriptions */
    if(random(3))
        return 0;
    /* slash attack descriptions */
    if(dt == W_SLASH)
    {
        to_me = "You attempt to hew " + QTNAME(enemy) + " with the " +
            TO->query_short() + " but miss widely.";
        to_enemy = QCTNAME(TP)+ " attempts to hew you with the " +
            TO->query_short() + " but misses you widely.";
        to_onlooker = QCTNAME(TP) + " attempts to hew " + QTNAME(enemy) +
            " with the " + TO->query_short() + " but misses widely.";
        
        if(phurt > 0)
        {
            to_me = "You tear a wound in " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + " and blood seeps out " +
                "of the gash.";
            to_enemy = QCTNAME(TP) + " tears a wound in your " + hdesc +
                " with the " + TO->query_short() + " and blood seeps out " +
                "of the gash.";
            to_onlooker = QCTNAME(TP) + " tears a wound in " + QTNAME(enemy) +
                "'s" + hdesc + " with the " + TO->query_short() + " and " +
                "blood seeps out of " + QTNAME(enemy) + "'s gash.";
        }
        if(phurt > 10)
        {
            to_me = "You slice " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ". The blood that " +
                "pours out of " + QTPNAME(enemy) + " wound is " +
                "blackened by the sword.";
            to_enemy = QCTNAME(TP) + " slices your " + hdesc + " with the " +
                TO->query_short() + ". The blood that pours out of your " +
                "wound is black.";
            to_onlooker = QCTNAME(TP) + " slices " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + ". Black blood " +
                "pours out of " + QTPNAME(enemy) + " wound.";
        }
        if(phurt > 25)
        {
            to_me = "You hack deep wounds in " + QTPNAME(enemy) + " " +
                hdesc + " with your " + TO->query_short() + ". " +
                QCTPNAME(enemy) + " exposed blood boils as if heated.";
            to_enemy = QCTNAME(TP) + " hacks deep wounds in your " + hdesc +
                " with the " + TO->query_short() + ". You feel like your " +
                "blood is boiling.";
            to_onlooker = QCTNAME(TP) + " hacks deep wounds in " +
                QTPNAME(enemy) + " " + hdesc + " with the " +
                TO->query_short() + ". " + QCTPNAME(enemy) + " bloody " +
                "wound appears to be boiling.";
        }
        if(phurt > 50)
        {
            to_me = "You ravage " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ". " + QCTPNAME(enemy) +
                " blood flows a deep black, as if emitting darkness.";
            to_enemy = QCTNAME(TP) + " ravages your " + hdesc + " with the " +
                TO->query_short() + ". Your blood flows a deep black, " +
                "as if emitting darkness.";
            to_onlooker = QCTNAME(TP) + " ravages " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + ". " +
                QCTPNAME(enemy) + " blood flows a deep black, as if " +
                "emitting darkness.";
        }
        if(phurt > 70)
        {
            to_me = "You annihilate " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ", leaving behind " +
                "only scarce traces of flesh and bone.";
            to_enemy = QCTNAME(TP) + " annihilates your " + hdesc +
                " with the " + TO->query_short() + ", leaving you with " +
                "hardly a trace of flesh or bone.";
            to_onlooker = QCTNAME(TP) + " annihilates " + QTPNAME(enemy) +
                " " + hdesc + " with the " + TO->query_short() +
                ", leaving behind only scarce traces of flesh and bone.";
        }
    }
    /* impaling attack descriptions */
    else
    {
        to_me = "You attempt to penetrate " + QTPNAME(enemy) + " " + hdesc +
            " with the " + TO->query_short() + " but miss widely.";
        to_enemy = QCTNAME(TP)+ " attempts to penetrate you with the " +
            TO->query_short() + " but misses you widely.";
        to_onlooker = QCTNAME(TP) + " attempts to penetrate " +
            QTNAME(enemy) + " with the " + TO->query_short() +
            " but misses widely.";

        if(phurt > 0)
        {
            to_me = "You pierce " + QTPNAME(enemy) + " " + hdesc +
                " with the " + TO->query_short() + " and blood " +
                "seeps out of the gash.";
            to_enemy = QCTNAME(TP) + " pierces your " + hdesc + " with the " +
                TO->query_short() + " and blood seeps out of the gash.";
            to_onlooker = QCTNAME(TP) + " pierces " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + " and blood " +
                "seeps out of " + QTNAME(enemy) + "'s gash.";
        }
        if(phurt > 10)
        {
            to_me = "You stab " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ". The blood that " +
                "pours out of " + QTPNAME(enemy) + " wound is " +
                "blackened by the sword.";
            to_enemy = QCTNAME(TP) + " stabs your " + hdesc + " with the " +
                TO->query_short() + ". The blood that pours out of your " +
                "wound is black.";
            to_onlooker = QCTNAME(TP) + " stabs " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + ". Black blood " +
                "pours out of " + QTPNAME(enemy) + " wound.";
        }
        if(phurt > 25)
        {
            to_me = "You puncture " + QTPNAME(enemy) + " " +
                hdesc + " with your " + TO->query_short() + ". " +
                QCTPNAME(enemy) + " exposed blood boils as if heated.";
            to_enemy = QCTNAME(TP) + " punctures your " + hdesc +
                " with the " + TO->query_short() + ". You feel like your " +
                "blood is boiling.";
            to_onlooker = QCTNAME(TP) + " punctures " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + ". " +
                QCTPNAME(enemy) + " bloody wound appears to be boiling.";
        }
        if(phurt > 50)
        {
            to_me = "You core " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ". " + QCTPNAME(enemy) +
                " blood flows a deep black, as if emitting darkness.";
            to_enemy = QCTNAME(TP) + " gores your " + hdesc + " with the " +
                TO->query_short() + ". Your blood flows a deep black, " +
                "as if emitting darkness.";
            to_onlooker = QCTNAME(TP) + " gores " + QTPNAME(enemy) + " " +
                hdesc + " with the " + TO->query_short() + ". " +
                QCTPNAME(enemy) + " blood flows a deep black, as if " +
                "emitting darkness.";
        }
        if(phurt > 70)
        {
            to_me = "You lance through " + QTPNAME(enemy) + " " + hdesc +
                " with your " + TO->query_short() + ", leaving behind " +
                "only scarce traces of flesh and bone.";
            to_enemy = QCTNAME(TP) + " lances through your " + hdesc +
                " with the " + TO->query_short() + ", leaving you with " +
                "hardly a trace of flesh or bone.";
            to_onlooker = QCTNAME(TP) + " lances through " + QTPNAME(enemy) +
                " " + hdesc + " with the " + TO->query_short() +
                ", leaving behind only scarce traces of flesh and bone.";
        }
    }
    enemy->catch_msg(to_enemy + "\n");
    E(TO)->catch_msg(to_me + "\n");
    E(TO)->tell_watcher(to_onlooker + "\n", enemy);
    return 1;
}
