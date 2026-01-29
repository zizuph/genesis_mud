inherit "/std/shadow"; 

race_sound() { return "ribbits"; }

destruct_toad_shadow()
{
  call_out("remove_shadow",43200);   //12 hours!
}


