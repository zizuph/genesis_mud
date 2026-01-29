/*
 * Pirate crew of a ship in the Turbidus Sea.
 *
 * Uses the layman pirate guild soul and specials.
 *
 * Arman, January 2021.
 */

#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE
inherit "/d/Krynn/std/equip";

#define WEP1   "/d/Ansalon/common/wep/sword/rapier"
#define WEP2   "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3   "/d/Ansalon/common/wep/sword/cutlass2"
#define WEP4   "/d/Ansalon/guild/pirates/obj/hook"
#define ARM1   "/d/Ansalon/guild/pirates/obj/patch"
#define ARM2   "/d/Ansalon/balifor/flotsam/obj/armour/shirt"
#define ARM3   "/d/Ansalon/balifor/flotsam/obj/armour/jerkin"
#define ARM4   "/d/Ansalon/guild/pirates/obj/pegleg"
#define ARM5   "/d/Ansalon/balifor/flotsam/obj/armour/bandana4"
#define ARM6   "/d/Ansalon/balifor/flotsam/obj/armour/bandana2"
#define BOTTLE "/d/Calia/gelan/objects/bottle"
#define LAMP   "/d/Krynn/solamn/palanthas/aesthetics/obj/mlantern_hooded"
#define OIL    "/d/Krynn/solamn/palanthas/aesthetics/obj/moil_flask"

#define MONEY  ({ 4, 8, 1, 0 })

#define PIRATE_SOUL    "/d/Ansalon/guild/pirates/soul/pirate_soul"
#define SS_GUILD_SPECIAL_SKILL   143030
#define PSTAGGER_OBJ   "/d/Ansalon/guild/pirates/obj/pirate_stagger"
#define PSTAGGER_AID   80

#define ATTACKED_PIRATES "_attacked_pirate_sailors"

#define DEBUG(x)   find_player("arman")->catch_msg("[pirate] " + x + "\n")

void get_me_soul();
object lamp, oil;

int soul_id;
object pstagger_obj;

void
clone_guild_items()
{
    TO->add_cmdsoul(PIRATE_SOUL);
}

public string
query_guild_name_lay()
{
    return "Pirate of the Bloodsea";
}

void
create_krynn_monster()
{
    set_name("pirate");
    add_name("_pirate_sailor");
    set_race_name("human");
    add_adj("bloodthirsty");
    set_short("bloodthirsty pirate");
    set_gender(G_MALE);
    set_long("Before you stands a drunken bloodthirsty pirate, itching " +
        "for battle and longing for the loot found on the fat merchant " +
        "ships that sail the Turbidus Ocean.\n");

    set_stats(({120, 120, 120, 100, 100, 120}));
    set_base_stat(SS_LAYMAN, 200);
    
    set_skill(SS_WEP_SWORD, 85);
    set_skill(SS_WEP_KNIFE, 85);
    set_skill(SS_2H_COMBAT, 85);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_ACROBAT, 85);
    set_skill(SS_BLIND_COMBAT, 65);
    set_skill(SS_AWARENESS, 65);
    set_skill(SS_GUILD_SPECIAL_SKILL, 100);

    add_prop(CONT_I_HEIGHT, 180 + random(10));
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    add_prop(OBJ_M_HAS_MONEY, MONEY);

    set_alignment(-400);
    set_knight_prestige(100);

    set_act_time(18);
    add_act("say The high seas are full of foolish landlubbers!");
    add_act("prub");
    add_act("ppirate pirate");
    add_act("plook");
    add_act("plaugh");
    add_act("phang");
    add_act("pbarnacle");
    add_act("pshow");
    add_act("pshow");
    add_act("pscramble");
    add_act("pthink");
    add_act("psmell");
    add_act("extinguish lamp");
    add_act("fill lamp with oil");

    set_all_hitloc_unarmed(25);

    // enhanced natural armour and pirate specials 
    // intoxicated (faster natural heal)
    set_exp_factor(115);

    equip(({
         (random(2) ? WEP2 : WEP4 ),
         (random(2) ? WEP1 : WEP3 ),
         (random(2) ? ARM5 : ARM6 ),
         ARM1, ARM2, ARM3, BOTTLE }));

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
}

void
fill_bottle(object bottle)
{
    int grog_type = random(100);

    bottle->set_soft(bottle->query_max());

    switch(grog_type)
    {
        case 0..30:
            bottle->set_filled_short(({"ale"}));
            bottle->set_alco(2 * bottle->query_max() / 100);
            break;
        case 31..50:
            bottle->set_filled_short(({"apple cider"}));
            bottle->set_alco(4 * bottle->query_max() / 100);
            break;
        case 51..70:
            bottle->set_filled_short(({"dark beer"}));
            bottle->set_alco(6 * bottle->query_max() / 100);
            break;
        case 71..90:
            bottle->set_filled_short(({"heavy red wine"}));
            bottle->set_alco(14 * bottle->query_max() / 100);
            break;
        default:
            bottle->set_filled_short(({"strong rum"}));
            bottle->set_alco(60 * bottle->query_max() / 100);
            break;
    }
    return;
}

void
get_me_soul()
{
    object bottle;

    add_cmdsoul(PIRATE_SOUL);
    update_hooks();
    remove_alarm(soul_id);
    command("wear patch");

    // Clone the evade - stagger object.
    if(!present("_pirate_stagger_object_", TO))
    {
        pstagger_obj = clone_object(PSTAGGER_OBJ);
        pstagger_obj->set_evade_combat_aid(PSTAGGER_AID);
        pstagger_obj->set_effect_caster(TO);
        pstagger_obj->set_effect_target(TO);
        pstagger_obj->move(TO, 1);
        pstagger_obj->start();
    }

    // Fill the bottle with a beverage
    if(present("bottle", TO))
    {
        bottle = present("bottle", TO);
        fill_bottle(bottle);
    }
}

void
light_lamps()
{
    if(CAN_SEE_IN_ROOM(TO))
        return;

    seteuid(getuid(this_object()));

    switch(random(8))
    {
        case 0:
            command("peer blindly");
            break;
        case 1:
            command("say Fog rolling in captain! Light the lamps!");
            break;
        case 2:
            command("say It getting dark? Bring out the lights!");
            break;
        default:
            break;
    }

    if(objectp(lamp))
    {
        command("fill lamp with oil");
        command("light lamp");
        return;
    }
    else
    {
        lamp = clone_object(LAMP);
        lamp->move(TO, 1);
        oil = clone_object(OIL);
        oil->move(TO, 1);
        command("emote grabs a lamp from below deck.");
        command("fill lamp with oil");
        command("light lamp");
    }

}

int
special_attack(object enemy)
{
    int attacktype, pen, att, wloc;
    mixed hitres;
    string *hitloc, *attack, how, weapon;

    // Activate pirate stagger evade.
    if(!TO->query_intoxicated())
    {
        TO->set_intoxicated(TO->intoxicated_max());
	tell_room(E(TO), QCTNAME(TO) + " looks well fortified " +
            "and ready for a rowdy fight!\n", ({ TO }));
    }

    if(!CAN_SEE_IN_ROOM(TO))
        light_lamps();

    command("drink from bottle");

    attacktype = random(3);

    if (attacktype == 0)
    {
        command("pbash");
        return 1;
    }

    return 0;
}

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_PIRATES))
        ob->add_prop(ATTACKED_PIRATES, 1);
}

void
attack_enemy_again(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    command("kill " +enemy->query_name());
    return;
}

void
attack_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {   
        set_alarm(6.5, 0.0, &attack_enemy_again(enemy));
        return;
    }

    command("kill " +enemy->query_name());
    return;
}

void
init_living()
{
    set_alarm(0.5, 0.0, &light_lamps());

    if(this_player()->query_prop(ATTACKED_PIRATES))
    {
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));
    }

    ::init_living();
}

