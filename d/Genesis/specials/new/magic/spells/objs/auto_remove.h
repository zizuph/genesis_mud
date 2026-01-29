/*
 * Auto Remove Header
 *
 * Include this header file in any spell effect object that you want
 * autoremoved.
 *
 * Created by Petros, September 2009
 */

/*
 * Function:    remove_spell_object
 * Description: Calls the base remove_object function
 */
public void
remove_spell_object()
{
    ::remove_object();
}

/*
 * Function:    remove_object
 * Description: This ensures that whenever this object is
 *              removed, it will first dispel all the effects, reversing
 *              any of the effects and doing proper cleanup.
 */
public void
remove_object()
{
    // We call dispel_effect, which in turn will call dispel_spell_effect.
    // This should roll back all effects
    dispel_effect(query_effect_caster());
    // No need to call base remove_object since dispel_effect will do so.
}
