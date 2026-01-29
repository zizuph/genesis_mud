// Serpentine staff  /d/Avenir/common/holm/obj/serpent_staff.c
// creator(s):   Lilith, 1/25/97
// purpose:      To be wielded by priestly students of the Beast
// last update:  Zizuph, Xmas 2021: converted to magic enhancing item.        
// note:         This object, when dropped, will transform into a 
//               serpent (see /holm/mon/staff_serpent.c)      
//              Benefits:
//              -If the owner/dropper is in combat when the staff
//               is dropped, the serpent will attack his enemies.
//               (I'm not sure how to calculate its combat aid.)
//              -The serpent can be easily handled by its owner.
//              Drawbacks:
//              -The serpent can be picked up by anyone who has
//               the right combination of skills.
//              -There is a 30 minute delay before the staff can 
//               be dropped again to form a serpent.
//              -If the serpent is killed the staff is broken.
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====

inherit "/d/Avenir/inherit/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#define SNAKEPROP    "_Avenir_snake_staff"
#define STAFFSNAKE   "/d/Avenir/common/holm/mon/staff_serpent"
/* 30 mins before useful as a serpent again*/
#define SNAKE_TIME    (600.0)

string my_long()
{
    return "A staff carved of alder wood stripped of its bark and "+
           "polished to a high sheen. It is wavy or serpentine "+
           "in form, and has scales carved into it. One end of the "+
           "staff is fashioned into the head of a snake, its mouth "+
           "open to reveal very real-looking fangs. The tail is barbed "+
           "with spikes not unlike the fangs.\n";
}

void create_weapon()
{
    set_keep(1);
    set_name("staff");    
    set_pname("staffs");
    add_name(({"polearm", "weapon"}));
    set_adj(({"serpentine"}));
    set_short("serpentine staff");
    set_pshort("serpentine staves");
    set_long(my_long());                                   
    set_hit(30);
    set_pen(25);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);

    add_item(({"head", "fangs", "mouth"}),
        "This is a very realistic-looking snake head. The artistry "+
        "of the carving is quite amazing, even down to the fangs "+
        "in the open, silently hissing mouth.\n");
    add_item(({"tail", "barb", "spike", "spikes"}), 
        "The tail is barbed with slightly curving spikes that occur "+
        "in a spiral around the end of the staff. They look quite "+
        "sharp.\n");

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,35) * 2); /* Magical */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This "+ short() +" is enchanted.\n", 10,
        "It is made of Alder, which when felled is white, but then\n"+
        "seems to bleed.\n", 15,
        "Alder is sacred as both the Tree of Fighting and the Tree\n"+
        "of Resurrection.\n", 20,
        "The Serpent God was invoked as this staff was carved.\n", 25,
        "When dropped, this staff will transform into a snake.\n", 30,
        "It will fight for you against your enemies, but if it dies\n"+
        "the staff will be broken and its magic forever lost.\n", 35,
        "One must be dextrous and skilled in handling animals if one\n"+
        "wishes to claim the serpent and thus transform it back into\n"+
        "a staff.\n", 40,
        "The staff requires a period of time to recharge its magical\n"+
        "properties before it can again transform itself into a snake."+
        "\n", 50}));
    add_prop(OBJ_S_WIZINFO, "This staff is enchanted. When dropped it "+
        "will transform itself into a serpent that will attack the "+
        "dropper's enemies. The staff requires a period of time to "+
        "recharge its magic before it can repeat the transformation. "+
        "The staff can be picked up while in its serpent-form, "+
        "however, it requires a DEX and SS_ANI_HANDL result > 0 "+
        "using TASK FORMIDABLE. If the serpent is killed, it will "+
        "transform back into the staff, broken, and useless.\n");
    seteuid(getuid());
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(46);
    set_spellpower_elements(({ SS_ELEMENT_LIFE, 
        SS_ELEMENT_AIR, SS_ELEMENT_EARTH }));
}

/* 
 * This function is called when this object is cloned
 * as a result of the serpent transformation.
 * It removes the magical effectiveness for 30 mins
 */
void remove_magic()
{
    add_prop(SNAKEPROP, 1);
    set_alarm(SNAKE_TIME, 0.0, "restore_magic");
}

/* 
 * This function is called SNAKE_TIME after this object is cloned
 * as a result of the serpent transformation.
 * It restores the magical effectiveness after 30 mins
 */
void restore_magic()
{
    if (query_prop(OBJ_I_BROKEN))
        return;

    remove_prop(SNAKEPROP);
}

/*
 * get_snake is called by the leave_env. 
 * It causes the snake transformation.
 */
void get_snake(object inv)
{
    object snake;
 
    if (!objectp(inv))
	return;

    snake = clone_object(STAFFSNAKE);
    snake->move(ENV(inv), 1);
    tell_room(ENV(inv), "The serpentine staff seems to shiver before "+
        "your eyes and then suddenly comes to life!\n");
    snake->set_owner(inv->query_real_name());
    snake->help_owner(inv);
    remove_object();
}

/*
 * Controls the snake transformation
 */
void leave_env(object inv, object to)
{
    ::leave_env(inv, to);    

    /* If a non-living env, stay a staff */
    if (!to || living(to))
      return;

    /* If broken, stay a staff */
    if (query_prop(OBJ_I_BROKEN))
      return;

    /* If magic isn't re-charged, stay a staff */
    if (query_prop(SNAKEPROP))
      return;

    /* Do snake transformation */
    else
    { 
        add_prop(SNAKEPROP, 1);
        set_alarm(1.0, 0.0, &get_snake(inv));
    }

}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
