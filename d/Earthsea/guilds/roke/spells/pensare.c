inherit "/d/Genesis/newmagic/spells/identify";

public void
create_spell()
{
  ::create_spell();
  set_spell_name("pensare");
  set_spell_desc("Identify magical properties.");
  set_spell_ingredients(({ "copper coin", "copper coin", "aspen bark" }));  
}
