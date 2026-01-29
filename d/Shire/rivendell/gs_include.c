/*
 * Prevent Dragons from being summoned in Rivendell and 
 * surrounding forests.
 * Taken from Gondor, Finwe March 2003
 */

// COMMENTED OUT by Palmer Mar 2003
// Forrest area was completely bugged

/*
void
load_gs_obj(object ob)
{
object gs_ob;


if (!objectp(ob))
return;


    if (present("_dragonarmy_horn", ob) &&
      !present("Gondor_Shire_object", ob))
{

        gs_ob->move(ob, 1);

    }
}

void
enter_inv(object ob, object from)
{
enter_inv(ob, from);

 
set_alarm(5.0, 0.0, &load_gs_obj(ob));

} 
*/