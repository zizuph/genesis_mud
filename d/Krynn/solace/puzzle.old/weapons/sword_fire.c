/* A sword of fire. ~solace/puzzle/weapons/sword_fire */

inherit "/std/weapon";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_weapon()
{
    set_name("sword of fire");
    add_name("sword");
    add_name("weapon");
    add_name("fire sword");
    set_pname("swords of fire");
    add_pname("swords");
    set_long("A very big broad sword encrusted with rubies. You notice that "+
        "@@wielded_desc@@it feels warm to the touch.\n");

    set_hit(32);
    set_pen(32);

    set_wf(TO);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({
      "This is a magic sword.", 3,
      "It will burst into flames as you wield it.", 18,
      "The fire will hurt your opponent additionally.", 29 }));
    add_prop(OBJ_S_WIZINFO,"This is a flame sword. When an enemy is hit, " +
	     "additional fire damage will be dealt to the enemy.\n");
    add_prop(OBJ_I_VOLUME, 4000); // 4 litres.
    add_prop(OBJ_I_WEIGHT, 15000); // 15 kilos.
    add_prop(OBJ_M_NO_BUY, 1);
					
}

string wielded_desc()
{
    return(objectp(query_wielded()) ? "a red fire plays along the surface "+
        "of the blade and " : "");
}

mixed wield(object obj)
{
    if(obj == TO)
    {
        change_prop(OBJ_I_LIGHT, 1);
	add_prop(OBJ_I_HAS_FIRE, 1);

        TP->catch_msg("The blade of the "+short()+" bursts into flame as "+
             "you wield it.\n");

        tell_room(E(TP), "The blade of "+QTNAME(TP)+"'s "+short()+" bursts "+
            "into flame as "+PRONOUN(TP)+" wields it.\n", TP);
        return 1;
    }
    else
        return 0;
}

mixed unwield(object obj)
{
    if(obj == TO)
    {
        change_prop(OBJ_I_LIGHT, 0);
	remove_prop(OBJ_I_HAS_FIRE);

        TP->catch_msg("As you stop wielding the "+short()+" the flames "+
            "are extinguished.\n");

        tell_room(E(TP), "As "+QTNAME(TP)+" stops wielding "+POSSESSIVE(TP)+
            " "+short()+", the flames playing along the blade are "+
            "extinguished.\n", TP);
        return 1;
    }
    else
        return 0;
}

int did_hit(int a, string b, int c, object en, int d, int e, int f)
{
    object fireball, me;

    if(c > 0) /* If the enemy is actually hit by the weapon. */
    {
        /* Produce a special attack on one in every five successful attacks. */

        if(!random(5))
        {
            me = query_wielded();

            switch(random(3))
            {
                case 0:
                {
                    me->catch_msg("A column of flame shoots out at "+QTNAME(en)+
                        " from the "+short()+", setting "+OBJECTIVE(en)+
                        " alight like a bonfire.\n");

                    en->catch_msg("A column of flame shoots out at you from "+
                        "the "+short()+" that "+QCTNAME(me)+" is wielding. "+
                        "Your skin catches fire and you smell your own flesh "+
                        "burning.\n");

                    tell_room(E(me), "A column of flame shoots out at "+
                        QTNAME(en)+" from the "+short()+" that "+QTNAME(me)+
                        " is wielding, setting "+OBJECTIVE(en)+" alight "+
                        "like a bonfire.\n", ({ en, me }));
                    break;
                }

                case 1:
                {
                    me->catch_msg("The "+short()+" glows brightly and a "+
                        "fireball shoots out at "+QCTNAME(en)+", engulfing "+
                        OBJECTIVE(en)+" in flame.\n");

                    en->catch_msg("The "+short()+" wielded by "+QTNAME(me)+
                        " glows brightly and a fireball shoots out at you, "+
                        "engulfing you in flame. You feel your skin beginning "+
                        "to melt.\n");

                    tell_room(E(me), "The "+short()+" wielded by "+QTNAME(me)+
                        " glows brightly and a fireball shoots out at "+
                        QTNAME(en)+", engulfing "+OBJECTIVE(en)+" in flame.\n",
                        ({ en, me }));
                    break;
                }

                case 2:
                {
                    me->catch_msg("The "+short()+" emits a ball of red flame "+
                        "which surrounds "+QTNAME(en)+".\n");

                    en->catch_msg("The "+short()+" that "+QTNAME(me)+" is "+
                        "wielding emits a ball of red flame which surrounds "+
                        "you, entrapping you in its sphere.\n");

                    tell_room(E(me), "The "+short()+" that "+QTNAME(me)+" is "+
                        "wielding emits a ball of red flame which surrounds "+
                        QTNAME(en)+", entrapping "+OBJECTIVE(en)+" in its "+
                        "sphere.\n", ({ en, me }));

                    if(!objectp(present("fireball", en)))
                    {
                        seteuid(getuid());
                        fireball = clone_object(OBJECTS + "fireball_obj");

                        fireball->move(en);
                        fireball->set_number_of_cycles(5 + random(6));
                        fireball->start_burning();
                    }
                    break;
                }
            }
            return 1;
        }
    }
    return 0;
}


void leave_env(object from, object dest)
{
    if(LIVING(from))
        if(!LIVING(dest))
            change_prop(OBJ_I_LIGHT, 0);

    ::leave_env(from, dest);
}

mixed query_recover()
{
    return 0;
}
