/* Stralle @ Genesis 040210
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/rituals/shadows/std_enchantment";

int
query_is_takhisis_unholy_water()
{
    return 1;
}

int is_ritual_object()
{
    return 1;
}

string
wizinfo_extra()
{
    return "(Un)holy water, is merely used for an ingredient.\n";
}

mixed *
query_identify_info()
{
    return ({
        "The dark waters in this vial sparkle with a life of " +
        "their own.\n", 2,
        "You recognise this as the holy water of Takhisis, used " +
        "by Her priesthood in their dark rituals.\n", 15,
        "This would no doubt would be deterant for the children " +
        "of Paladine and His likes.\n", 75,
        });
}

mixed
enchant_object(object obj)
{
    if (member_array("vial", obj->query_names()) < 0 &&
        member_array("_std_potion_vial", obj->query_names()) < 0)
        return "The enchantment has no effect on the " + obj->short() + ".";

    allbb("The contents of the " + obj->short() + " grows darker " +
        "and sparkles begin to rise from it.\n");

    set_enchantment_strength(80);
    
    return 0;
}

varargs void
remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    if (!quiet && objectp(obj))
    {
        allbb("Suddenly the contents of the " + obj->short() +
            " turns transparent again.\n");
    }
}
