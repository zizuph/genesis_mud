/*
 * Pendant worn to heal players and lower their align. A gift from the 
 * Dark Lord to ensnare the Haradrim
 *
 * Finwe, August 2005
 */


#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";

int worn;
int max_heal = 7500;
int poison_chance = 5;

public void create_object()
{
    setuid(); 
    seteuid(getuid());
    set_name("pendant");
    add_adj(({"black", "smooth"}));
    set_short("smooth black pendant");
    set_long("This is a smooth black pendant. It is triangular shaped with rounded corners. It is wafer thin and the size of a hand. The pendant seems unusually light for something this big .\n");
 
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    set_slots(A_NECK);
    set_layers(1);
    set_looseness(5);

}
 
 
public string
query_auto_load()
{
    return MASTER + ":";
}
 
public string
query_recover()
{
    return 0;
}

void init() 
{
}


wear(object obj)
{
    write("You dip your head slightly and place the " + short() + " around your neck.\n");
    say(QCTNAME(this_player()) + " dips " + HIS_HER(TP) + " head slightly and places the " + short() + " around " + HIS_HER(TP) + " neck.\n");

    
    return 0;
}


remove (object obj)
{
    write("You dip your head slightly and remove the " + short() + " from around your neck.\n");
    say(QCTNAME(this_player()) + "dips " + HIS_HER(TP) + " head slightly and removes the " + short() + " from around " + HIS_HER(TP) + " neck.\n");
    

    return 0;
}

void
lower_align()
{
    int check_align;

    check_align = TP->query_alignment();

    switch(check_align)
    {
        case 730..1200:     // Blessed, Saintly, Holy
        {
            TP->adjust_alignment(50);
            // lower 50
            break;
        }
        case 460..729:      // Sweet, Good, Devout
        {
            TP->adjust_alignment(30);
            // lower 30
            break;
        }
        case 190..459:      // Trustworthy, Sympathetic, Nice
        {
            TP->adjust_alignment(15);
            // lower 15
            break;
        }
        case 100..189:      // Agreeable
        {
            TP->adjust_alignment(5);
            // lower 5
            break;
        }

        case 99..-79:       // Neutral
        {
            TP->adjust_alignment(3);
            // lower 3
            break;
        }
        case -80..-239:     // Disagreeable, Untrustworthy
        {
            TP->adjust_alignment(5);
            // lower 5
            break;
        }
        case -240..-469:    // Unsympathetic, Sinister, Wicked
        {
            TP->adjust_alignment(5);
            // lower 5
            break;
        }
        case -470..-699:    // Nasty, Foul, Evil
        {
            TP->adjust_alignment(10);
            // lower 10
            break;
        }
        case -700..-769:    // Malevolent
        {
            TP->adjust_alignment(20);
            // lower 20
            break;
        }
        case -770..-849:    // Beastly
        {
            TP->adjust_alignment(30);
            // lower 30
            break;
        }
        case -850..-929:    // Demonic
        {
            TP->adjust_alignment(40);
            // lower 40
            break;
        }
        case -930..-1200:   //Damned
        {
            TP->adjust_alignment(50);
            // lower 50
            break;
        }
    }
}