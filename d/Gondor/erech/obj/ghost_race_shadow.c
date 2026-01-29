/*
 * Howl shadow
 *
 * To add shadow to any living:
 *   object shadow = clone_object(path_to_this_shadow);
 *   shadow->shadow_me(real name or object of player/living to shadow);
 * To remove (for example):
 *   Call living/player remove_howl_shadow
 *
 */

inherit "/std/shadow";

/* 
 * This function helps removing this shadow - to remove it you can
 * call function remove_howl_shadow() in living with howl shadow.
 */
public int
remove_howl_shadow()
{
   tell_object(query_shadow_who(), "Howl shadow removed.\n");
   remove_shadow();
   return 1;
}

/*
 * Here you mask race_sound() and change it to return "howl" to everyone.
 * (code of race_sound() is in /std/living/cmdhooks.c)
 */
public string
race_sound()
{
   return "howls";
}





