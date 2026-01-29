/* 
 * Elmore, Dec. 2015. Wyrllish Parkane guildmaster of the draconians
 * Based on prist in Neraka by Ashlar, 30 Aug 97
 *
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/spells.h"
#include "/d/Ansalon/guild/pot/obj/living/npc.h"

inherit "/d/Ansalon/guild/pot/obj/living/npc";

#define ARM2 NARM + "crescent_shield"
#define ARM3 NARM + "black_chain_shirt"
#define WEP1 NWEP + "mace1h"

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif


int gMoveBehind;
static int last_heal;
object pouch, needle, nails, eyes, hearts, spoon;

void arm_me();

void
create_pot_monster()
{
    if(!IS_CLONE)
	return;

    set_name("Wyrllish");
    add_name("human");
	add_name("wyrllish");
    set_living_name("wyrllish");
    set_race_name("human");
    set_adj("bald");
	add_adj("deformed");
    set_gender(G_MALE);
    set_long("Infront of you stands a deformed bald human, dressed in the "+
	  "traditional robe of the Priests of Takhisis. He is slowly caressing "+
	  "the dragon eggs as he mumbles incoherently to himself. He seems "+
	  "confident and wise in the ways of draconians and Takhisis.\n"+
	  "You might want to ask him about draconians.\n"+
	  "He is wearing a deep-black shimmering robe.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({
        145 + random(20),
        155 + random(20),
        180 + random(20),
        195 + random(35),
        185 + random(25),
        170 + random(20)
    }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          85);
    set_skill(SS_DEFENCE,           85);
    set_skill(SS_PARRY,             75);
    set_skill(SS_AWARENESS,         85);
    set_skill(SS_SPELLCRAFT,        100);
    set_skill(SS_ELEMENT_LIFE,      100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_AIR,      100);
    set_skill(SS_FORM_DIVINATION,   75);
    set_skill(SS_FORM_ENCHANTMENT,  100);
    set_skill(SS_FORM_ABJURATION,   75);
    set_skill(SS_FORM_TRANSMUTATION, 75);
    set_skill(SS_HERBALISM, 100);
	
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_SEE_INVIS, 20);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_skill(PS_GUILD_LEVEL, 200);
    set_skill(PS_SPELLS, PBLIND_ID | PSLOW_ID | PTALON_ID | PHEAL_ID | PPAIN_ID);
    set_all_hitloc_unarmed(30);
	set_title("and Guild Master of the Draconians of Krynn");
    set_alignment(-1150);
    set_knight_prestige(500);
	set_introduce(1);
	arm_me();
}

int
check_health()
{
    return (100 * ::query_hp()) / query_max_hp();
}

int
query_hp()
{
    int hp;

    hp = ::query_hp();

    /* Heal if we need too */
    if (((time() - last_heal) > 10)
        && ((!query_attack() && check_health() < 100) || check_health() <= 17))
    {
        // heal some mana :)
        add_mana(25);
        command("pheal");

        last_heal = time();
    }
    
    return hp;
}

void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));

    clone_object(WEP1)->move(this_object(),1);
    command("wield all");

    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    command("wear all");

    pouch = clone_object("/d/Ansalon/guild/pot/obj/comp_pouch");

    for(int i = 0; i < 20; i++)
    {
        clone_object("/d/Krynn/common/herbs/bch_willow")->move(pouch, 1);
        clone_object("/d/Krynn/common/herbs/tiger_lily")->move(pouch, 1);
        clone_object("/d/Krynn/common/herbs/greenslime")->move(pouch, 1);

        spoon = clone_object("/d/Ansalon/taman_busuk/neraka/wep/spoon");
        spoon->add_prop(OBJ_M_NO_STEAL, 1);
        spoon->move(pouch, 1);
    }

    needle = clone_object("/d/Ansalon/guild/pot/obj/needle");
    needle->add_prop(OBJ_M_NO_STEAL, 1);
    needle->move(this_object(), 1);

    nails = clone_object("/std/leftover");
    nails->leftover_init("nail", "human");
    nails->set_heap_size(20);
    nails->move(pouch, 1);

    eyes = clone_object("/std/leftover");
    eyes->leftover_init("eye", "human");
    eyes->set_heap_size(10);
    eyes->move(pouch, 1);

    hearts = clone_object("/std/leftover");
    hearts->leftover_init("heart", "elf");
    hearts->set_heap_size(20);
    hearts->move(pouch, 1);

    hearts = clone_object("/std/leftover");
    hearts->leftover_init("heart", "human");
    hearts->set_heap_size(20);
    hearts->move(pouch, 1);

    TO->add_prop("_i_have_money", 1);
    TO->add_prop("_obj_m_has_money", 1);
    MONEY_MAKE_GC(30)->move(pouch, 1);

    pouch->move(this_object(), 1);
 
    ::arm_me();
}

public string
query_guild_title_occ()
{
	return "Parkane";
}

int
is_team_enemy(object o)
{
    if (member_array(o->query_attack(), query_team_others() + ({ TO })) >= 0)
        return 1;
    else
        return 0;
}

int
special_attack(object enemy)
{
    int health, mana;
    int enemy_health;
    int is_blinded, is_slowed, is_pained;
    object *enemies;

    if (query_prop(LIVE_I_CONCENTRATE))
        return 0;

#ifdef 0
    if (gMoveBehind)
        gMoveBehind--;
#endif

    if (random(2))
        return 0;

    if (!random(3))
    {
        /* Check to see if we want to switch enemy */

        int i,sm,smi;
        
        enemies = (filter(all_inventory(E(TO)),is_team_enemy) |
        query_team_others()->query_attack() | ({ enemy })) - ({ 0 });

        for (i=0,sm=999,smi=-1; i<sizeof(enemies); i++)
        {
            int j;
            j = enemies[i]->query_average_stat() + random(15);
            if ((j < sm) && (!P(PAIN_ID, enemies[i])))
            {
                sm = j;
                smi = i;
            }
        }
        if (smi >= 0)
        {
            enemy = enemies[smi];
            command("kill " + enemy->query_real_name());
            DEBUG("New enemy: " + enemy->query_real_name());
        }
    }
#ifdef 0
    /* move behind/rescue is now in the templeguard
     * priests always teams with templeguards
     */
    else if (!gMoveBehind)
    {
        /* Try to move behind another if we are attacked */

        object *team;

        team = TO->query_team_others();
        team = filter(team,&->id("_templeguard_"));

        if (sizeof(team))
        {
            object mb;
            int i;

            mb = team[random(sizeof(team))];
            if (E(mb) == E(TO))
            {
                int told = 0;

                enemies = FILTER_LIVE(all_inventory(E(TO)));

                for (i=0; i<sizeof(enemies); i++)
                {
                    if (enemies[i]->query_attack() == TO)
                    {
                        if (!told)
                        {
                            tell_room(E(TO),QCTNAME(TO) + " withdraws " +
                            "behind " + QTNAME(mb) + ", leaving the latter " +
                            " to face " + QTNAME(TO) + "'s attackers.\n",
                            ({ TO, mb }));
                            DEBUG("MB " + mb->query_real_name());
                            told = 1;
                            gMoveBehind = 10;
                        }
                        enemies[i]->attack_object(mb);
                        mb->attack_object(enemies[i]);
                    }
                }
            }
        }
    }
#endif

    health = (query_hp() * 100) / query_max_hp();
    mana = (query_mana() * 100) / query_max_mana();

    is_blinded = objectp(P(BLIND_ID,enemy));
    is_slowed  = objectp(P(SLOW_ID,enemy));
    is_pained  = objectp(P(PAIN_ID,enemy));

    /* Check our health! */
    if ((health < 35) && (mana > 5))
    {
        command("pheal");
        return 0;
    }

    if (!is_pained && random(2))
    {
        command("ppain " + enemy->query_real_name());
        return 0;
    }


    if (!is_blinded)
    {
        command("pblind " + enemy->query_real_name());
        return 0;
    }

    if (!is_slowed)
    {
        command("pslow " + enemy->query_real_name());
        return 0;
    }

    if (random(3)) {
        command("ptalon " +enemy->query_real_name());
        add_mana(50);
        return 0;
    }
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

	if (ob->query_guild_name_race() == "Draconians of Krynn")
	{
		TO->command("shout You are not worthy of being a draconian. Begone!\n");
		ob->command("raceleave");
	}
    // To avoid bouncing.
    this_object()->heal_hp(700);
}
