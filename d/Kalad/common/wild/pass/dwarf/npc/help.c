void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote grins viciously and get a wild look in the eyes.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}   
