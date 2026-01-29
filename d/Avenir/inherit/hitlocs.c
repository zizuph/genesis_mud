/* Lets make the hitlocs look a bit prettier and more descriptive */
/*    -Cirion, May 30 1996 */

string translate_hitloc(object who, string hitloc)
{
  string   str;

  /* We need to be humanoid to use this! */
  if(!function_exists("create_monster", who) && !interactive(who))
   return hitloc;

  if(!strlen(hitloc))
   return hitloc;

  if(hitloc == "legs") // Get rid of the silly plurals
   hitloc = (random(2) ? "right" : "left") + " leg";

  if(hitloc == "head" && random(2))
   hitloc = (random(2) ? "face" : "throat");
  else if(strlen(hitloc) && sscanf(hitloc, "%s arm", str) && random(2))
   hitloc = (random(2) ? "lower " + hitloc : str + " shoulder");
  else if(strlen(hitloc) && sscanf(hitloc, "%s leg", str) && random(2))
   hitloc = (random(2) ? "lower " + hitloc : str + " thigh");
  else if(hitloc == "body" && random(2))
   hitloc = (random(2) ? "chest" : "stomach");

  return hitloc;
}
