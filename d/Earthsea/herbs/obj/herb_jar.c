/*
 * Coded by Ckrik 6/21/14
 *
 * Ckrik 7/10/2015 Fixed formatting
 * New herb jar for Earthsea
 */

#pragma strict_types

inherit "/std/receptacle";
inherit "/lib/keep";

#include <macros.h>
#include <herb.h>
#include <stdproperties.h>

public void
create_receptacle()
{
    set_keep();
    set_name("jar");
    add_name("_ckriks_herb_jar");
    add_name("equipment");
    set_pname("jars");
    set_adj("blue");
    add_adj(({"large", "herb", "glass"}));
    set_short("blue glass herb jar");
    set_pshort("blue glass herb jars");
    set_long("A large transparent blue jar. " +
        "The colour prevents the herbal contents from " +
        "decaying. You notice a small mark on the " +
        "bottom of the jar. The top has a lid, making it " +
        "possible to open and close.\n");
    add_item(({"mark", "small mark", "bottom", "bottom of jar",
        "bottom of the jar"}), "On the bottom of the jar is a " +
        "small rune, signifying Made In Gont.\n");
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_LIGHT, 0);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
}

public int
prevent_enter(object ob)
{
    if(!ob->id("herb"))
    {
        write("The jar is for herbs only.\n");
        return 1;
    }

    return 0;
}

int comparator(object *a, object *b)
{
    string aname = a[0]->query_herb_name();
    string bname = b[0]->query_herb_name();

    if (aname < bname) return (-1);
    if (aname > bname) return (1);
    return 0;
}

void describe_herbs(object *herbs, object fo)
{
    if (sizeof(herbs) == 0) return;

    int quantity = 0;
    foreach(object herb : herbs) quantity += herb->num_heap() || 1;

    string herb_description = herbs[0]->singular_short();
    string herb_name = herbs[0]->query_herb_name();
    mixed *eff = herbs[0]->query_effect();
    string eff_name = eff[1];
    string str;
    if (eff_name == "hp")
    {
        eff_name = "health";
    }
    if (eff[2] < 0)
    {
        str = "neg";
    }
    else
    {
        switch (eff[2])
        {
        case 0..24:
            str = "min";
            break;
        case 25..49:
            str = "norm";
            break;
        default:
            str = "maj";
            break;
        }
    }

    fo->catch_tell(sprintf("| %-:16s | %-:32s | %-:8s | %-:4s | %3d |\n",
        herb_name, herb_description, eff_name, str, quantity));
}

void describe_special(object *herbs, object fo)
{
    if (sizeof(herbs) == 0) return;

    int quantity = 0;
    foreach(object herb : herbs) quantity += herb->num_heap() || 1;
    string herb_name = herbs[0]->query_herb_name();
    string herb_description = herbs[0]->singular_short();

    fo->catch_tell(sprintf("| %-:16s | %-:32s | %-:8s | %-:4s | %3d |\n",
        herb_name, herb_description, "   -", " -", quantity));
}

void describe_unknown(object *herbs, object fo)
{
    if (sizeof(herbs) == 0) return;

    int quantity = 0;
    foreach(object herb : herbs) quantity += herb->num_heap() || 1;
    string herb_description = herbs[0]->singular_short();

    fo->catch_tell(sprintf("| %-:16s | %-:32s | %-:8s | %-:4s | %3d |\n",
        "        -", herb_description, "   -", " -", quantity));
}

int filter_heal(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_HEALING && eff[2] >= 0 && ob->do_id_check(fo);
}

int filter_harm(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_HEALING && eff[2] < 0 && ob->do_id_check(fo);
}

int filter_enhance(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_ENHANCING && ob->do_id_check(fo);
}

int filter_poison(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_POISONING && ob->do_id_check(fo);
}

int filter_cure(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_CURING && ob->do_id_check(fo);
}

int filter_special(object fo, object ob)
{
    mixed *eff = ob->query_effect();
    if (eff == 0)
    {
        return 0;
    }
    return eff[0] == HERB_SPECIAL && ob->do_id_check(fo);
}

int filter_unknown(object fo, object ob)
{
    return !ob->do_id_check(fo) || ob->query_effect() == 0;
}

void describe_contents(object fo, object *obarr)
{
    function f_heal = &filter_heal(fo, ); 
    function f_harm = &filter_harm(fo, ); 
    function f_enhance = &filter_enhance(fo, ); 
    function f_poison = &filter_poison(fo, ); 
    function f_cure = &filter_cure(fo, ); 
    function f_special = &filter_special(fo, ); 
    function f_unknown = &filter_unknown(fo, ); 

    if (sizeof(obarr) == 0)
    {
        fo->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    mixed *rest_herb = sort_array(unique_array(filter(obarr, f_heal), "query_herb_name"), comparator);
    mixed *harm_herb = sort_array(unique_array(filter(obarr, f_harm), "query_herb_name"), comparator);
    mixed *enhance_herb = sort_array(unique_array(filter(obarr, f_enhance), "query_herb_name"), comparator);
    mixed *poison_herb = sort_array(unique_array(filter(obarr, f_poison), "query_herb_name"), comparator);
    mixed *cure_herb = sort_array(unique_array(filter(obarr, f_cure), "query_herb_name"), comparator);
    mixed *special_herb = sort_array(unique_array(filter(obarr, f_special), "query_herb_name"), comparator);
    mixed *unknown_herb = sort_array(unique_array(filter(obarr, f_unknown), "query_herb_name"), comparator);

    if (sizeof(rest_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Restore)     Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : rest_herb) {
            describe_herbs(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(enhance_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Enhance)     Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : enhance_herb) {
            describe_herbs(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(cure_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Cure)        Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : cure_herb) {
            describe_herbs(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(harm_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Harmful)     Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : harm_herb) {
            describe_herbs(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(poison_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Poison)      Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : poison_herb) {
            describe_herbs(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(special_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Herb (Special)     Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : special_herb) {
            describe_special(herbs, fo);
        }
        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
    if (sizeof(unknown_herb) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Unidentified       Description                        Type       Str    Qty  \n" +
            "+------------------+----------------------------------+----------+------+-----+\n");

        foreach(object *herbs : unknown_herb) {
            describe_unknown(herbs, fo);
        }

        fo->catch_tell(
            "+------------------+----------------------------------+----------+------+-----+\n");
    }
}
