/*
 * nsniff.c
 */


/*
 * Function name: query_mana_cost
 * Description:   returns the mana cost of this spell
 * Arguments:     target - the target of the spell
 * Returns:       the cost in mana of this spell
 */
public int
query_mana_cost(object target)
{
     if (target == TP)
	  return 10;
     else
	  return 20;
}

/*
 * Function name: query_magic_skill
 * Description:   returns the magic skill needed for this spell
 * Returns:       the cost in mana of this spell
 */
public int
query_magic_skill()
{
     return SS_FORM_DIVINATION;
}

/*
 * Function name: query_magic_form
 * Description:   returns the magic skill needed for this spell
 * Returns:       the cost in mana of this spell
 */


/*
 * Function name: query_spell_class
 * Description:   returns the spell class (per magic03 man page)
 * Returns:       the class number of this spell
 */
public int
query_spell_class()
{
     return 1;
}

/*
 * Function name: nsniff
 * Description:   detect good alignment in the target
 * Arguments:     str - 
 * Returns:       1/0
 */
nomask int
nsniff(string str)
{
     object who;

     NF("Nsniff whom?\n");

     if (str)
	  who = present(lower_case(str), ENV(TP));

     if (!who) {
	  if ((!str) || (str == me) || (str == "myself"))
	       who = TP;
	  else
	       return 0;
     }

     NF("Some force prevents your magic.\n");
     if (NPMAGIC(who))
	  return 0;

     
}

