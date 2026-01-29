/********************* no *************************************************/

int
no()
{
    write("You shake your head firmly and begin to explain...\n");
    all(" shakes " + POSSESSIVE(TP) + " head firmly "
      + "and begins to explain...");
    return 1;
}

/********************* philosophy *****************************************/

int
philosophy()
{
    write("You think about the universe as such and soon come up with "
      + "a completely new theory.\n");
    all(" pauses to think about the mysteries of the universe, "
      + "and soon comes up with an entirly new theory.");
    return 1;
}


