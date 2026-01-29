/*
 * 2003-09-25 by Dargoth
 * a weapon bearing minor enchantment allowing
 * the wielder to hit particular race harder.
 *
 * Race is determined at random on weapon startup.
 * Weapons like those were created by the Thanar Knights in their
 * quest for human domination. Initially they was supposed to give
 * advantage over any non-human race, however, this is a not a
 * top quality weapon and was enchanted by minor casters, who only
 * concentrated on the sense that non-humans were gnats,
 * ie. smaller. Hence the nickname "gnatslayer" for those weapons
 * and the erratic weapon's 'recognition' of minor races.
 * The weapon was constructed for human use, therefore other
 * races will have lesser performance when trying to wield it.
 * To use it properly the wielder needs to have a decent club skill
 * and stats.
 * the extra dmg calculation and disenchant function taken from
 * /doc/examples.
 */
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/lib/commands";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <options.h>
#include <filter_funs.h>

#define TP (this_player())
#define TO (this_object())
#define HE(X) ((X)->query_pronoun())
#define HIS(X) ((X)->query_possessive())
#define ENV(X) (environment((X)))
#define MIN_CLUBSKILL 59
#define MIN_INT 61
#define MACE_SKILLED "_mace_wielded_properly"
#define MACE_ENHANCED "_mace_wielded_by_hunam"

#define HIT 30
#define PEN 25

#define ADDHIT 15
#define ADDPEN 15
#define DMG_MOD (200 - random(50))

#define LOGTHIS(X)  log_file("gnattest", sprintf("%s\t%s\n",ctime(time()),(X)))

/* the amount of fatigue given to player if he
    fails to wield the mace */
#define TRY_WIELD 50

string enemy_race;
status enchanted=1; // initially mace is enchanted, but this can be dispelled

public int disenchant_object(object disenchanter);

void create_weapon()
{
    set_name(({ "gnatslayer","mace", "club" }));
    set_adj(({"alloyed", "burnished", "blackened", "steel"}));
    set_short("burnished steel mace");
    set_long("The weapon consists of a medium-length piece of dark brown "+
        "seasoned wood, reinforced with metal rings, atop which is set a "+
        "burnished ball of alloyed steel. The handle is carved a bit "+
        "to allow for better grip, if the wielder has the proper hand "+
        "shape.\n");

    enemy_race= ({ "dwarf", "gnome", "goblin", "hobbit", "kender" })[random(5)];
    // enemy_race="goblin";

    set_hit(HIT);
    set_pen(PEN);
    set_hands((random(2)?W_RIGHT:W_LEFT));
    set_wf(TO);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_likely_corr(3); /*  the steel has been made resistant,
                              however, that doesn't mean it is acid-immune */

    set_likely_dull(0); // there is nothing to dull there... not a bladed thing

    set_likely_break(2); /* well you can try to break the wooden handle,
                        however, since it is protected by metal rings,
                        that shouldn't be easy */

    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO,({ "The mace seems to bear an enchantment.\n",15,
        "It has been enchanted to deal more damage against a particular "+
        "type of beings.\n", 30,
        "It was made specifically for humans, and the wielder "+
        "needs to be skilled and intelligent "+
        "to be able to use the weapon effectively.\n",40,
        "The mace deals two-fold damage when it hits a "+enemy_race+".\n",60,
        "Maces such as these were called \"gnatslayers\" and used frequently "+
        "by the Knights of Thanar in their crusade against lesser races. "+
        "Since the enchantment is somewhat crude and erratical, "+
        "each mace will crush a single race only and "+
        "will have its full power only in the hands of a human.\n",90 }));

    add_prop(OBJ_S_WIZINFO,"This is a mace bearing a minor enchantment, "+
        "enhancing damage against a particular type of beings. "+
        "To use it properly, the wielder needs to have decent skills "+
        "and stats.\n");

    add_prop(OBJ_I_WEIGHT, 5000 + random(1500));
    add_prop(OBJ_I_VOLUME, 1520);
    // it's magical, so we make it more costly
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(49, 40) + 1000);

    set_keep(1);

}

mixed
wield(object wep)
{

    if (!enchanted)
        return 0;

    if (!(TP->query_race() == "human" && TP->query_race_name() =="human" ))
    {
        if (TP->query_fatigue() > TRY_WIELD && TP->resolve_task(TASK_DIFFICULT,
            ({ TS_INT, SKILL_WEIGHT, 60, SS_WEP_CLUB })))
        {
            write("You manage to get a comfortable grip on the handle "+
            "of the "+short()+" even though it was not made for your "+
            "kind of hand.\n");
            allbb(" gets a practised grip on the "+short()+".");
            add_prop(MACE_SKILLED,1);
            set_hit(query_hit()+ADDHIT);
            set_pen(query_pen()+ADDPEN);
            return 1;
        }
        allbb(" gropes at the "+short()+", but fails to wield it.\n");
        TP->add_fatigue(-TRY_WIELD);
        return "You try to wield the "+short()+", however, you can't "+
            "get a decent grip on the handle, which was obviously "+
            "made for a different kind of hand.\n";
    }

    /* if a human, the mace was made for human hand, so we just check
       the skill */
    if (TP->query_skill(SS_WEP_CLUB) > MIN_CLUBSKILL)
    {
        write("With a practised grip, you wrap your hand around the "+
            short()+", and you feel a sort of frenzied feeling wash over you.\n");
        allbb(" gets a practised grip on the "+short()+".");
        TP->command("smile malignant");
        set_hit(query_hit()+ADDHIT);
        set_pen(query_pen()+ADDPEN);
        add_prop(MACE_SKILLED,1);
        add_prop(MACE_ENHANCED,1);
        return 1;
    }
    return 0;
}

int unwield(object wep)
{
    if (query_prop(MACE_SKILLED) && enchanted)
    {
        set_hit(query_hit()-ADDHIT);
        set_pen(query_pen()-ADDPEN);
        remove_prop(MACE_SKILLED);
    }
    remove_prop(MACE_ENHANCED);
    return 0;
}

public varargs int did_hit(int aid, string hdesc, int phurt,
    object enemy, int dt, int phit, int dam)
{

    int resistance;
    object me=TP;
    string his=HIS(me);
    string he=HE(me);
    string sdesc=short();
    string hitname=" lightly strikes ";
    string i_do, he_does;
    string emote;

    if (TP->query_wiz_level() > 0)
       write(sprintf("==== aid: %d, hd: %s, phurt: %d\n==== phit: %d, dam: %d\n",
                aid,hdesc, phurt, phit, dam));

    if (phurt > 0 && query_prop(MACE_ENHANCED) && enemy->query_race_name() == enemy_race)
    {
        switch (phurt)
        {
            case 1..29: hitname=" strikes ";
                    break;
            case 30..50: hitname=" lands a blow on ";
                        break;
            case 51..70: hitname=" smashes into ";
                        break;
            case 71..100: hitname=" smites ";
        }

        switch (random(3))
        {
               case 0: emote="grin";
               		break;
               case 1: emote="grunt";
               		break;
               case 2: emote="howl";
               		break;
               	default:
               		emote="smile";
        }

        resistance = enemy->query_prop(MAGIC_I_RES_MAGIC);

        switch (resistance)
        {
            case 0..30:
                actor("You "+emote+", as your "+sdesc+hitname+"the "+
                hdesc+" of",({ enemy }));
                me->tell_watcher(QCTNAME(me)+" "+emote+"s, as "+his+" "+
                	sdesc+hitname+"the "+hdesc+" of "+QTNAME(enemy)+".\n",
                	enemy );
                target(" "+emote+"s as "+his+" "+sdesc+hitname+" your "+hdesc,
                ({ enemy }));
                break;
            case 31..60:
                actor("You "+emote+", as your "+sdesc+hitname+"the "+hdesc+
            		" of",({ enemy }));
                me->tell_watcher(QCTNAME(me)+" "+emote+"s as "+he+hitname+
                	"the "+hdesc+" of "+QTNAME(enemy)+" with "+his+
                	" "+sdesc+".\n", enemy);
                target(emote+"s as "+he+hitname+"your "+hdesc+" with "+his+
                    " "+sdesc,({ enemy }));
                break;
            case 61..80:
                actor("Your "+sdesc+" vibrates slightly as it"+hitname+
                "the "+hdesc+" of",({ enemy }) );
                me->tell_watcher(QCTNAME(me)+"'s "+sdesc+" vibrates slightly "+
                	"as "+he+hitname+"the "+hdesc+" of "+QTNAME(enemy)+".\n",
                	enemy);
                target("'s "+sdesc+" vibrates slightly as "+he+hitname+"your "+
                	hdesc, ({ enemy }));
                break;
            default:
                /* if enemy has high resistance, the enchantment might be
                   dispelled automagically */
                 actor("Your "+sdesc+" screeches and a blueish light ripples "+
                    "along its length, as it connects with the "+hdesc+" of",
                 	({ enemy }));
                 me->tell_watcher(QCTNAME(me)+"'s "+sdesc+" screeches as it "+
                 	"connects with the "+hdesc+" of "+QTNAME(enemy)+
                 	"!\n",enemy);

                 target("'s "+sdesc+" screeches as it connects with your "+
                 	hdesc,({ enemy }));
                 if (random(8))
                        set_alarm(0.2, 0.0, disenchant_object,enemy);
        }

        /* Do the extra damage, taking the magic resistance into account */
        if (TP->query_wiz_level()>0)
           write(sprintf("==== Extra dam: %d\n", DMG_MOD * (100 - resistance) / 100));

        enemy->hit_me(DMG_MOD * (100 - resistance) / 100, MAGIC_DT, TP, -1);

        /* Kill the target, if appropriate */
        if (enemy->query_hp() <= 0)
        {
            enemy->command("gasp");
            enemy->command("drop wielded items");
            enemy->do_die(TP);
        }
        return 1;
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

public int
disenchant_object(object disenchanter)
{
    if (!enchanted)
        return 0;

    if (query_wielded())
        unwield(TO);

    /* Reset magical properties */
    remove_prop(OBJ_I_IS_MAGIC_WEAPON);
    remove_prop(MAGIC_AM_MAGIC);

    enchanted=0;

    add_prop(MAGIC_AM_ID_INFO, ({
        "This item has once possessed some magic, but now it is gone.\n", 20 }));

    /* It isn't worth as much without the magic */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

    write("A ripple of red light passes over your "+short()+", leaving it "+
    "looking it in some inexplicible way plainer then before.\n");
    allbb("watches as a red light ripples over "+HIS(TP)+" "+short()+".");

    return 1;
}
