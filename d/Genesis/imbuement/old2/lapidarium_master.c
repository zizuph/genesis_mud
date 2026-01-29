/*
 *  /d/Genesis/imbuement/lapidarium_master.c
 *
 *  Master object to handle lapidariums
 *  Object that players carry is /d/Genesis/imbuement/obj/lapidarium.c
 *
 *  2010/10/25 Lavellan
 *
*/
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "imbuement.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */
#define     DATAFILE        "/d/Genesis/imbuement/lapidarium_data"

/* Global Variables */
mapping     data = ([]);
int         alarm_save;

/* Prototypes */
public void                 create();
public int                  store(object ply, object obj);
public string               extract(object ply, string arg);
public string               check(string pnam);
public int                  quality_rank(string qual);
public void                 load();
public void                 save();
public void                 updated();


/*
 * Function name:        create
 * Description  :        initial setup
 */
public void
create()
{
    setuid();
    seteuid(getuid());

    data = restore_map(DATAFILE);
//    set_alarm(0.0, 0.0, load);
} /* create */


/*
 * Function name:        store
 * Description  :        store a stone into someone's lapidarium contents
 * Arguments    :        object ply - player doing the storing
 *                       object obj - stone they are trying to store
 * Returns      :        int - 0: Didn't work for some reason
 *                             1: Worked
 */
public int
store(object ply, object obj)
{
    string pnam, type;
    int qual, num;
    mapping rec;
    int *nums;

    //None of these should never happen!
    if ((!ply) || (!obj))
    {
        write("ERROR!\n");
        return 0;
    }
    if (!obj->id(STONE_NAME))
    {
        write("ERROR: Not a stone!\n");
        return 0;
    }
    if (environment(obj) != ply)
    {
        write("ERROR: Not in inventory!\n");
        return 0;
    }

    type = obj->query_stone_type();
    qual = quality_rank(obj->query_stone_quality());

    if ((!type) || (!qual))
    {
        write("There seems to be something wrong with that stone. Please" +
            " contact a wizard.\n");
        return 0;
    }

    pnam = ply->query_real_name();
    rec = data[pnam];
    if (rec)
        nums = rec[type];
    else
        rec = ([]);
    if (!nums)
    {
        nums = allocate(5);
    }
    nums[qual-1]++;
    rec[type] = nums;
    data[pnam] = rec;

    updated();

    return 1;
} /* store */


/*
 * Function name:        extract
 * Description  :        remove a stone from someone's lapidarium contents
 *                       and clone the stone for them
 * Arguments    :        object ply - player doing the extracting
 *                       string arg - what they typed
 *                       string qual - quality of stone they want
 * Returns      :        string - message to show to player
 */
public string
extract(object ply, string arg)
{
    string pnam, qual, type;
    int qualn;
    mapping rec;
    int *nums, num, i, pl;
    object stone;

    //Should never happen!
    if (!arg)
    {
        return "ERROR!\n";
    }

    pnam = ply->query_real_name();
    rec = data[pnam];
    if (!rec)
        return "You would need to store something in your lapidarium before" +
            " you could extract anything.";

    if (!parse_command(arg, this_player(), "%w %w", qual, type))
    {
        type = arg;
        qual = 0;
    }

    if ((type != "lars") && (type[-1..] == "s"))
    {
        type = type[..-2];
        pl = 1;
    }

    if (type[-5..] != "stone")
        type += "stone";

    if (type[..4] == "stone") 
        if (m_sizeof(rec) == 1)
        {
            type = m_indices(rec)[0];
        }
        else
            return "Please be more specific. Which type of stone do you wish" +
                " to extract?";

    if (qual)
    {
        qualn = quality_rank(qual);
        if (!qualn--)
            return "But " + qual + " is not a stone quality. Possible qualities" +
                " are cracked, blemished, ordinary, unblemished, or glittering.";
    }

    nums = rec[type];
    if (!nums)
        return "You don't have any " + type + "s in your lapidarium.";

    if (qual)
    {
        num = nums[qualn];
        if (!num)
            return "You don't have any " + qual + " " + type + "s in your" +
                " lapidarium.";
    }
    else
    {
        qualn = -1;
        for (i=0; i <= 4; i++)
            if (nums[i])
            {
                if (qualn >= 0)
                    return "You have more than one type of " + type +
                        " in your lapidarium. Please be more specific.";
                else
                    {
                    qualn = i;
                    num = nums[i];
                    }
            }
    }
    qual = ({ "cracked", "blemished", "ordinary",
        "unblemished", "glittering" })[qualn];

    for (i = (pl ? num : 1); i > 0; i--)
    {
        nums[qualn]--;

        stone = clone_object(IMBUE_DIR + "obj/imbuement_stone");
        stone->set_stone_type(type);
        stone->set_stone_quality(qual);
        stone->move(ply, 1);
    }

    if (!(nums[0] + nums[1] + nums[2] + nums[3] + nums[4]))
        m_delkey(rec, type);

    if (!m_sizeof(rec))
        m_delkey(data, pnam);

    updated();

    if ((pl) && (num > 1))
    {
        tell_room(environment(ply), QCTNAME(ply) + " extracts " +
            LANG_NUM2WORD(num) + " " + stone->short() + "s from " +
            ply->query_possessive() + " lapidarium.\n", ply);
        return "You extract " + LANG_NUM2WORD(num) + " " + stone->short() + 
            "s from your lapidarium.";
    }
    else
    {
        tell_room(environment(ply), QCTNAME(ply) + " extracts " +
            LANG_ADDART(stone->short()) + " from " + ply->query_possessive() +
            " lapidarium.\n", ply);
        return "You extract " + LANG_ADDART(stone->short()) + 
            " from your lapidarium.";
    }
}


/*
 * Function name:        check
 * Description  :        retrieve contents of player's lapidarium
 * Arguments    :        string pnam - name of player
 * Returns      :        string - lapidarium contents display
 */
public string
check(string pnam)
{
    string out = "";
    mapping rec = data[pnam];
    int numtypes, nulls, *stones, col, r, i, n;
    string type, *stypes;
    
    if (!rec)
        return "Your lapidarium is empty! You can <store> any stones used" +
            " for enchantment that you might have.\n";

    stones = rec["nullstone"];
    if (stones)
        nulls = stones[2];

    numtypes = m_sizeof(rec);
    if (nulls)
        numtypes--;

    if (numtypes)
    {
        stypes = sort_array(m_indices(rec));
        stypes -= ({"nullstone"});
        out = "          ";
        out = "\n" +
            out + "Your Lapidarium currently contains the following stones:\n" +
            out + "========================================================\n" +
            out + "Ckd = Cracked      Ord = Ordinary       Glt = Glittering\n" +
            out + "Blm = Blemished    Unb = Unblemished\n" +
            out + "========================================================\n" +
            out + " You may <store> or <extract> to add or remove stones.\n" +
            "\n";

        if (numtypes > 5)
            col = 1;

        if (col)
            out +=
                " +------------+------------------------..------------+------------------------+\n" +
                " | Stone Type |   Quantities Owned     || Stone Type |   Quantities Owned     |\n" +
                " |     by     +----+----+----+----+----+|     by     +----+----+----+----+----+\n" +
                " |    Name    |Ckd |Blm |Ord |Unb |Glt ||    Name    |Ckd |Blm |Ord |Unb |Glt |\n" +
                " +============+====+====+====+====+====++============+====+====+====+====+====+\n";
        else
            out +=
                " +------------+------------------------+\n" +
                " | Stone Type |   Quantities Owned     |\n" +
                " |     by     +----+----+----+----+----+\n" +
                " |    Name    |Ckd |Blm |Ord |Unb |Glt |\n" +
                " +============+====+====+====+====+====+\n";

        for (r = 0; r < numtypes; r++)
        {
            if (!col)
                n = r;
            else
            {
                n = r / 2;
                if (col == 2)
                    n += (numtypes % 2 ? numtypes + 1 : numtypes) / 2;
            }
            type = stypes[n];
            stones = rec[type];
            type = capitalize(type[0..-6]);
            if (col != 2)
                out += " ";
            //out += sprintf("| %-11s|%4d|%4d|%4d|%4d|%4d|", capitalize(type),
            //    stones[0], stones[1], stones[2], stones[3], stones[4]);
            out += sprintf("| %-11s|", type);
            for (i = 0; i <=4 ; i++)
            {
                n = stones[i];
                if (n)
                    out += sprintf("%-4d|", n);
                else
                    out += "    |";
            }
            if (col != 1)
                out += "\n";
            if (col)
                col = 3 - col;
        }

        if ((numtypes % 2) && col)
            out += "|            |    |    |    |    |    |\n";
        if (col)
            out += " +------------+----+----+----+----+----''------------+----+----+----+----+----+\n";
        else
            out += " +------------+----+----+----+----+----+\n";
    }

    if (nulls)
        out += "In a side compartment you " + 
            (numtypes ? "also have " : "have ") + 
            (nulls == 1 ? "a single nullstone" :
            LANG_NUM2WORD(nulls) + " nullstones") +
                ".\n";

//    out += "\n    You may <store> or <extract> to add or remove stones.\n";

    return out;
} /* check */

/*
 * Function name:        quality_rank
 * Description  :        change a string quality description to a number
 * Arguments    :        string qual - name of quality level
 * Returns      :        int - level, or 0 if not recognised
 */
public int
quality_rank(string qual)
{
    int rank;
    rank = member_array(qual, ({ "cracked", "blemished", "ordinary",
        "unblemished", "glittering" }) );
    if (rank == -1)
        rank = member_array(qual, ({ "ckd", "blm", "ord", "unb", "glt" }) );
    return rank + 1;
} /* quality_rank */


/*
 * Function name:        load
 * Description  :        loads data from file
 */
public void
load()
{
    data = restore_map(DATAFILE);
} /* load */


/*
 * Function name:        save
 * Description  :        saves data to file
 */
public void
save()
{
    save_map(data, DATAFILE);
} /* save */


/*
 * Function name:        updated
 * Description  :        sets timer to save data
 *                       if armageddon active, save straight away
 */
public void
updated()
{
    if (alarm_save)
        remove_alarm(alarm_save);

    alarm_save = 0;

    if (ARMAGEDDON->shutdown_active())
    {
        save();
    }
    else
    {
        alarm_save = set_alarm(30.0, 0.0, save);
    }
} /* updated */
