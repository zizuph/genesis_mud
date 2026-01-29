/*
 * City Administration Office
 *
 * Ashlar, 23 Jun 98
 *
 * This is the main administration object for a coherent
 * handling of the city of Neraka. It will be used to
 * implement the Mayor of Neraka office.
 *
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/taman_busuk/neraka/city.h"
#include DL_CLOCK

#define DEBUG(x)    (find_player("ashlar")->catch_msg("CITYADMIN: " + x + "\n"))

/*
 * Prototypes
 */

void save_cityState();
void load_cityState();
varargs void update_cityState(int force_report = 0);

/*
 * Global variables. These are saved with the object
 */

int gTax;
int gMoney;
mixed *gIncome;
mixed *gExpenses;
int gLastMoney;
int gLastMonth;
int gLastYear;
mapping gProfits;

static int updating;

void
create_room()
{
    set_short("Neraka City Administration Office");
    set_long("This is the administration office for the city of Neraka.\n");

    gTax        = 10;
    gMoney      = 0;
    gIncome     = ({ });
    gExpenses   = ({ });
    gLastMoney  = 0;
    gLastMonth  = 0;
    gLastYear   = 0;
    gProfits    = ([ ]);

    updating = 0;

    load_cityState();
}

/*
 * Function name: set_tax
 * Description:   Set the taxation of the businesses
 */
public void
set_tax(int tax)
{
    update_cityState();
    
    if (tax > 0 && tax < 50)
    {
        gTax = tax;
        save_cityState();
    }
}

/*
 * Function name: query_tax
 * Description:   Query the tax level
 */
public int
query_tax()
{
    return gTax;
}

/*
 * Function name: set_money
 * Description:   Set the amount of money in the treasury
 */
public void
set_money(int money)
{
    update_cityState();
    
    if (money >= 0)
    {
        gMoney = money;
        save_cityState();
    }
}

/*
 * Function name: query_money
 * Description:   Query the amount of money in the treasury
 */
public int
query_money()
{
    update_cityState();
    
    return gMoney;
}

/*
 * Function name: add_money
 * Description:   Add money to the treasury
 * Arguments:     money - the amount of money to add, or negative to remove
 *                account - the account to hold money / remove money
 * Returns:       the amount of money added, or removed
 */
public int
add_money(int money, mixed account)
{
    update_cityState();
    
    if (money > 0)
    {
        gMoney += money;
        gIncome += ({ account, money });
        save_cityState();
    }
    else if (money < 0)
    {
        gMoney += money;
        gExpenses += ({ account, money });
        save_cityState();
            
        return -money;
    }

    return money;
}

/*
 * Function name: pay_money
 * Description:   Removes the indicated amount of money
 * Arguments:     money - how much to remove
 * Returns:       Actual amount of money removed
 */
public int
pay_money(int money, mixed account)
{
    return add_money(-money, account);
}

/*
 * Function name: can_pay
 * Description:   Check if the treasury has enough money to pay an amount
 *                The treasury can contain a negative amount of money,
 *                if not all debts are paid. In that case, can_pay will
 *                fail until positive balance has been restored.
 */
public int
can_pay(int amount)
{
    update_cityState();
    
    if (gMoney >= amount)
        return 1;
    else
        return 0;
}

/*
 * Function name: report_profit
 * Description:   A subject reports in a profit through this function
 * Arguments:     profit - the profit
 *                subject - the subject (ID string)
 */
public void
report_profit(int profit, string subject)
{
    update_cityState();
    
    if (gProfits[subject])
        gProfits[subject] += profit;
    else
        gProfits[subject] = profit;
}

/**********/

varargs void
update_cityState(int force_report = 0)
{
    string filename, str, strtax;
    string *subjects;
    int *timearray = GET_TIME;
    int i, sum1, sum2;

    if (updating)
        return;

    if ((timearray[1] == gLastMonth) && (timearray[0] == gLastYear) && !force_report)
        return;

    /* Set the updating flag so that we won't be recursively called */
    updating = 1;

    /* Collect taxes from the reported profits */

    subjects = m_indexes(gProfits);
    strtax = "Tax breakdown:\n\n";
    sum1 = 0;

    for (i = 0; i < sizeof(subjects); i++)
    {
        int money = (gTax * gProfits[subjects[i]]) / 100;
        // Future modifier: a slight adjustment on the money,
        // depending on the subject in question

        strtax += sprintf("  %30s: %10d cc\n", subjects[i], money);
        sum1 += money;
        
        add_money(money, "Taxes");
    }

    strtax += sprintf("\n  %30s: %10d cc\n\n", "Total", sum1);

    /* Pay salaries */

    /* Create the monthly report */

    filename = NLOG + "r" + gLastYear + "_" + gLastMonth;
    rm(filename);

    str = sprintf("Report for the month of %s in the year %d.\n",
        MONTH_DATA[gLastMonth][0], gLastYear);

    str += "Balance sheet:\n\n";
    str += sprintf("  Positive balance from last month: %10d cc\n\n", gLastMoney);
    str += "  Income this month:\n";

    sum1 = 0;
    for (i = 0; i < sizeof(gIncome); i+=2)
    {
        str += sprintf("    %30s: %10d cc\n", gIncome[i], gIncome[i+1]);
        sum1 += gIncome[i+1];
    }
    str += sprintf("\n                             Total: %10d cc\n\n", sum1);

    str += "  Expenses this month:\n";

    sum2 = 0;
    for (i = 0; i < sizeof(gExpenses); i+=2)
    {
        str += sprintf("    %30s: %10d cc\n", gExpenses[i], gExpenses[i+1]);
        sum2 += gExpenses[i+1];
    }
    str += sprintf("\n                             Total: %10d cc\n\n", sum2);

    i = gLastMoney + sum1 + sum2;

    if (i != gMoney)
        str += sprintf("                   Unaccounted for: %10d cc\n\n", gMoney - i);

    str += sprintf("                           Balance: %10d cc\n\n", gMoney);
    
    write_file(filename, str);
    write_file(filename, strtax);

    gLastMoney = gMoney;
    gLastMonth = timearray[1];
    gLastYear = timearray[0];
    gExpenses = ({ });
    gIncome = ({ });
    gProfits = ([ ]);

    updating = 0;
}

void
save_cityState()
{
    if (updating)
        return;
    
    setuid();
    seteuid(getuid());

    save_object("/d/Ansalon/taman_busuk/neraka/admin/city_save");
}

void
load_cityState()
{
    if (updating)
        return;
    
    setuid();
    seteuid(getuid());

    restore_object("/d/Ansalon/taman_busuk/neraka/admin/city_save");
}
