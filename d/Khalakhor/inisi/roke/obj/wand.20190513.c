/*
 * A recoded version of the Roke healing wand, converted to
 * the new magic system. 10 heal charges, that recharge
 * one charge every 30 minutes.
 *
 * Coded by Arman 2017.
 */

inherit "/d/Genesis/specials/examples/std_magic_obj";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()

void set_ident_limit(int i);

string idshort, idlong;
string unidshort, unidlong;

int ident_limit, identified, recharging;

int charges = 10;

public int
query_wand_charges()
{
    return charges;
}

public void
set_wand_charges(int i)
{
    charges = i;
}

public void
recharge_wand()
{
    if((charges < 10) && recharging)
    {
        charges += 1; 
        TP->catch_msg("Your " +short()+ " throbs briefly.\n");    
    }

    if((charges < 10))
    {
        set_alarm(1800.0, 0.0, &recharge_wand());
        recharging = 1;
    }
    else
        recharging = 0;

}

/* 
 * Function : enter_env
 * Descript : update wand identify status
 */
public void
enter_env(object dest, object old)
{  
    if (!living(dest))
    {
        identified = 0;
        return;
    }

    if ((dest->query_skill(SS_SPELLCRAFT) + dest->query_stat(SS_WIS)) >
        (2 * ident_limit))
        identified = 1;
    else
        identified = 0;
}

/* 
 * Function : mylong
 * Descript : returns the long desc of the wand, depending on
 *            if the wand has been id'd or not
 */
public string
mylong()
{
    if (identified)
        return idlong;
    else
        return unidlong;
}

/* Function : set_long
 * Descript : set long description for unid'd wand
 */
void
set_long(string s)
{
    unidlong = s;
}
/* Function : set_short
 * Descript : set short description for unid'd wand
 */
void
set_short(string s)
{
    unidshort = s;
}

/* Function : set_id_short
 * Descript : set short description for id:d wand
 */
public void
set_id_short(string s)
{
    idshort = s;
    set_ident_limit(ident_limit);
}

/* Function : set_id_long
 * Descript : set long description for id:d wand
 */
public void
set_id_long(string s)
{
    idlong = s;
}

/*
 * Function : myshort
 * Descript : returns the short desc of the the wand, depending on
 *            if the wand is id'd or not
 */
public string
myshort()
{
    if (identified)
        return idshort;
    else
        return unidshort;
}

/* Function : set_ident_limit
 * Descript : set how hard it is to identify wand
 *            this value is used together with WIS & SPELLCRAFT
 *            to determine if player recognizes wand immediately
 */
public void
set_ident_limit(int i)
{
    ident_limit = i;

}

public void
create_magic_obj()
{
    set_name("wand");
    add_name("stick");
    set_adj("strange");
    add_adj("wooden");
    add_adj("healing");

    set_short("strange wooden stick");
    set_long("A grey stick. It looks a little mysterious.\n");
    set_id_long("This is a wand of healing.\n");
    set_id_short("wand of healing");

    ::set_long("@@mylong");
    ::set_short("@@myshort");

    set_ident_limit(25);

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 450);
    add_prop(MAGIC_AM_ID_INFO, ({"This strange mysterious stick " +
        "is actually a wand of healing. When held, one can 'zap' " +
        "the wand at themselves or others, making them feel better. " +
        "The wand has a limited number of healing charges, however " +
        "these do recharge over time. The effectiveness of the wand " +
        "is dependent on the users spellcraft skill.\n", 25}));
    add_prop(MAGIC_AM_MAGIC, ({25, "enchantment"}));
        
    set_slots(W_ANYH);
    set_keep(1);
    set_holdable(1);
    
    add_magic_obj_spell("[the] 'wand' [of] [healing]", ({ "zap" }),
        "/d/Khalakhor/inisi/roke/obj/wand_heal_spell.c");

    set_alarm(10.0, 0.0, &recharge_wand());
}

/*
 * Function name:   verify_magic_obj_spell_cast
 * Description:     
 * Arguments:       (string) arg - the argument which has been parsed
 *                  (object) spell - the spell object being cast
 * Returns:         (status) 1 - successfully attempting the spell
 *                           0 - the spell has been hindered
 */
public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!charges)
    {
        TP->catch_msg("Your " +short()+ " has run out of charges.\n");
        if(!recharging)
            set_alarm(1.0, 0.0, &recharge_wand());
        return 0;
    }

    charges -= 1;
    if(!recharging)
        set_alarm(1.0, 0.0, &recharge_wand());

    return 1;
} /* verify_magic_obj_spell_cast */

/* Function: identify_me
 * Descript: this function should be called by someone who wants
 *           to identify the wand permanently. (That is, a npc 
 *           wandidentify-shop or something.)
 * Returns : 1 if success, 0 else
 */
public int
identify_me()
{
    int i;

    i = TP->query_skill(SS_SPELLCRAFT) + TP->query_stat(SS_WIS);

    i = i / 2;

    if (random(i) < ident_limit)
    {
        /* success */

        ::set_long(idlong);
        ::set_short(idshort);
        return 1;
    }
    else
        return 0;
}

string
query_recover()
{
    return MASTER + ":" +charges;
}
 
void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    charges = atoi(a[0]);

    ::init_keep_recover(arg);
}