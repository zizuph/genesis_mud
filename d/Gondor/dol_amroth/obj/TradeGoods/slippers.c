/* -*- Mode: C -*-
 *
 * pumps.c
 *
 * Pumps to be sold in Dol Amroth
 *
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

/* Globale variables */
public string        color;

/* Prototypes */
string      long_desc();
string      short_desc();
string      pshort_desc();
//void set_color(string a);

void
create_object()
{
  /*
    if (color == "")
        color = "brown";
  */
    set_name("slippers");
    add_name("shoes");
    add_adj("suede");
    add_adj(color);
    set_short(&short_desc());
    set_pshort(&pshort_desc());
    set_long(&long_desc());

    set_slots(A_FEET);

    set_layers(1);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE,   75);
}

string
short_desc()
{ return "pair of "+color+" slippers"; }

string
pshort_desc()
{ return "pairs of "+color+" slippers"; }

string
long_desc()
{ return "This is a pair slippers. It seems like they are made " +
    "out of suede leather. They are coloured "+color+".\n"; }

/*
 * We need to override leave_env() so that we can be sure to remove
 * the anklet if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

void set_color(string a) { color = a; }
