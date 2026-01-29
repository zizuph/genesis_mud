/* 
 * /d/Calia/std/fruit.c
 * 
 * Suggested standard fruit
 *
 * Coded by Maniac 2/12/94
 */

inherit "/std/food";

#include <composite.h>

#define FRUIT_MAX_MANA 10
#define FRUIT_MAX_HP 20
#define FRUIT_MAX_FATIGUE 10
#define FRUIT_MIN_AMOUNT 80
#define F_FRUIT_PRICE(a, m, f, h) \
           5 + ((a * a) / 600) + ((500 * (m + f + h)) / a)

int mana_amount, hp_amount, fatigue_amount;


/*
 * Function name: set_mana_add
 * Description:   set the possible mana increase on eating the fruit
 * Arguments:     i - the possible mana increase
 */
public void
set_mana_add(int i) 
{ 
    if (i > FRUIT_MAX_MANA)
        mana_amount = FRUIT_MAX_MANA; 
    else if (i < 0)
        mana_amount = 0;   
    else 
        mana_amount = i;
}



/*
 * Function name: set_hp_add
 * Description:   set the possible hp increase on eating the fruit
 * Arguments:     i - the possible hp increase
 */
public void
set_hp_add(int i) 
{ 
    if (i > FRUIT_MAX_HP)
        hp_amount = FRUIT_MAX_HP; 
    else if (i < 0)
        hp_amount = 0;   
    else 
        hp_amount = i;
}


/*
 * Function name: set_fatigue_add
 * Description:   set the possible hp increase on eating the fruit
 * Arguments:     i - the possible hp increase
 */
public void
set_fatigue_add(int i) 
{ 
    if (i > FRUIT_MAX_FATIGUE)
        fatigue_amount = FRUIT_MAX_FATIGUE; 
    else if (i < 0)
        fatigue_amount = 0;   
    else 
        fatigue_amount = i;
}


/*
 * Function name:       query_fatigue_amount
 * Description:         Gives the max amount of fatigue adding in this fruit
 * Returns:             Fatigue amount as int 
 */
public int
query_fatigue_amount() {return fatigue_amount; }


/*
 * Function name:       query_mana_amount
 * Description:         Gives the max amount of mana adding in this fruit
 * Returns:             Mana amount as int 
 */
public int
query_mana_amount() {return mana_amount; }


/*
 * Function name:       query_hp_amount
 * Description:         Gives the max amount of hp adding in this fruit
 * Returns:             Hp amount as int 
 */
public int
query_hp_amount() {return hp_amount; }


/* Stop people calling set_amount from create_fruit() */
private void
set_amount(int a)
{
    ::set_amount(a);
}



/* Function name: set_fruit_amount
 * Description:   sets the nutritional value of the fruit
 * Arguments:     a: the nutritional value
 */
void
set_fruit_amount(int a)
{
  if (a < 0) a = 0;
  set_amount(FRUIT_MIN_AMOUNT + a);
}


/* Function name: special_effect
 * Description:   produce the effects that have been set in the fruit 
 *                when it is eaten
 * Arguments:     i - the number of this fruit type that have been eaten
 */

void
special_effect(int i)
{
    object tp = this_player();
    int x, total_mana_inc, total_hp_inc, total_fatigue_inc; 
    int hp_inc, mana_inc, fatigue_inc;
    string *wordlist = ({ });

    mana_inc = ((tp->query_mana() < tp->query_max_mana())
                   && mana_amount);
    hp_inc = ((tp->query_hp() < tp->query_max_hp()) 
                  && hp_amount);
    fatigue_inc = ((tp->query_fatigue() < tp->query_max_fatigue())
                      && fatigue_amount);
    
    if (!mana_inc && !hp_inc && !fatigue_inc)
        return;

    if (mana_inc) {
        for (x = 0; x < i; x++)
            total_mana_inc += random(mana_amount + 1);
        if (total_mana_inc) {
            tp->add_mana(total_mana_inc);
            wordlist += ({ "mentally stronger" });
        }
    }
    if (hp_inc) {
        for (x = 0; x < i; x++)
            total_hp_inc += random(hp_amount + 1);
        if (total_hp_inc) {
            tp->heal_hp(total_hp_inc);
            wordlist += ({ "healthier" });
        }
    }
    if (fatigue_inc) {
        for (x = 0; x < i; x++)
            total_fatigue_inc += random(fatigue_amount + 1);
        if (total_fatigue_inc) {
            tp->add_fatigue(total_fatigue_inc);
            wordlist += ({ "less tired" });
        }
    }
    if (sizeof(wordlist))
        tp->catch_msg("You feel " + COMPOSITE_WORDS(wordlist) + ".\n");
}


void
config_split(int new_num,mixed orig)
{
    ::config_split(new_num, orig);
    set_mana_add(orig->query_mana_amount());
    set_fatigue_add(orig->query_fatigue_amount());
    set_hp_add(orig->query_hp_amount());
}


/*
 * Function name: stat_object
 * Description:   Called when a wizard wants to get more info about
 *                an object.
 * Returns:       str - the string to write 
 */
string
stat_object()
{
    string str;
    int price, am;

    str = ::stat_object();

    str += "Mana benefit: ";
    if (mana_amount)
        str += "up to " + mana_amount + ".\n"; 
    else
        str += "0.\n";
    str += "Hp benefit: ";
    if (hp_amount)
        str += "up to " + hp_amount + ".\n";   
    else
        str += "0.\n";
    str += "Fatigue benefit: ";
    if (fatigue_amount)
        str += "up to " + fatigue_amount + ".\n"; 
    else
        str += "0.\n";

    am = query_amount();
    price = F_FRUIT_PRICE(am, mana_amount, fatigue_amount, hp_amount);
    str += "Correct price: " + price + " cc.\n"; 
    return str;
}


public varargs string
long(object for_obj)
{
    string str;
    string *words = ({ });
 
    if (mana_amount) words += ({ "recuperate your mental energy" });
    if (hp_amount) words += ({ "improve your physical health" });
    if (fatigue_amount) words += ({ "alleviate your tiredness" }); 

    if (mana_amount || fatigue_amount || hp_amount)
        str = "This food may " + COMPOSITE_WORDS(words) + " a " +
              "little, if you should be in need of it.\n";
    else
        str = "";

    return ::long(for_obj) + str; 
}

void
create_fruit()
{
}


void
create_food()
{
    set_amount(FRUIT_MIN_AMOUNT);
    create_fruit();
}

