#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

create_weapon()
{
    set_name("sword");
    add_name("sabre");

    set_adj("blue-pommeled");
    add_adj("curved");
    add_adj("large");
    set_short("blue-pommeled curved sabre");
    set_long("This is a well-balanced sabre with a long curved blade. " +
             "A solid guard protects the hands while the pommel is tightly " +
             "wrapped by a blue decorative rope that, besides adding style to " +
             "the sabre, grants a better grip.\n");
    set_default_weapon(45+random(8), 45+random(8), W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_likely_dull(1);
    set_likely_break(1);
    set_wf(TO);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT,  F_WEIGHT_DEFAULT_WEAPON(49, W_SWORD));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(49, 49));
    add_prop(OBJ_S_WIZINFO, "This two handed sabre has a large guard that makes " +
             "parrying easier. It also allows the wielder to hit the enemy with " +
             "the pommel when he parries a blow.\n");
}

mixed
wield(object what)
{
    TP->set_skill_extra(23, 10);
    wielder = TP;
    return 0;
}

mixed
unwield(object what)
{
    TP->set_skill_extra(23, 0);
    return 0;
}

void
pommel_hit(object att, object player)
{
    int index;
    
    string* how_wielder = ({"swiftly hit "+QTNAME(att)+" with the pommel of your sabre",
                            "hit "+QTNAME(att)+" with the pommel of your sabre with full force",
                            "bash "+QTNAME(att)+" with the pommel of your sabre",
                            "strike "+QTNAME(att)+" with the pommel of your sabre"});

    string* how_attacker = ({" swiftly hits you with the pommel of "+HIS(player)+" sabre",
                             " hits you with the pommel of "+HIS(player)+" sabre with full force",    
                             " bashes you with the pommel of "+HIS(player)+" sabre",
                             " strikes you with the pommel of "+HIS(player)+ " sabre"});

    string* how_watcher = ({"swiftly hit "+QTNAME(att)+" with the pommel of "+HIS(player)+" sabre",
                            "hit "+QTNAME(att)+" with the pommel of "+HIS(player)+" sabre with full force",
                            "bash "+QTNAME(att)+" with the pommel of "+HIS(player)+" sabre",
                            "strike "+QTNAME(att)+" with the pommel of "+HIS(player)+ " sabre"});


    index = random(4);
    
    player->catch_msg("As you parry the blow you "+how_wielder[index]+".\n");
    att->catch_msg("As "+QTNAME(player)+" parries the blow "+HE(player)+how_watcher[index]+".\n");
    tell_room(environment(player), "As "+QTNAME(player)+" parries the blow "+HE(player)+how_attacker[index]+".\n", ({player, att}));
    att->hit_me(175 + random(175), W_BLUDGEON, player, -1, -1);
}


public varargs void
did_parry(object att, int aid, int dt)
{
    string* names;
    string ob_id;
    object wielder;
    
    names = att->query_names();
    for(int i = 0, numNames = sizeof(names); i < numNames; i++)
    {
        string* broken_name = explode(names[i], "ob_");
        if(sizeof(broken_name) == 2)
        {
            ob_id = broken_name[1];
        }
    }

    if(ob_id)
    {
        wielder = query_wielded();
        if(wielder)
        {
            query_wielded()->add_prop("_sabre_did_parry", ob_id);
        }
    }
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam, int hid)
{

    string* names;
    string ob_id;
    object wielder;

    wielder = query_wielded();
    
    names = enemy->query_names();
    for(int i = 0, numNames = sizeof(names); i < numNames; i++)
    {
        string* broken_name = explode(names[i], "ob_");
        if(sizeof(broken_name) == 2)
        {
            ob_id = broken_name[1];
        }
    }

    if(ob_id && wielder && wielder->query_prop("_sabre_did_parry") == ob_id)
    {
        pommel_hit(enemy, wielder);
        wielder->remove_prop("_sabre_did_parry");
    }
    else if(wielder && wielder->query_prop("_sabre_did_parry"))
    {
        wielder->remove_prop("_sabre_did_parry");
    }
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
}
