program 
  var N as int ; 
  var SQRT as int ; 
begin 
  N := readint ; 
  SQRT := 0 ; 

  while SQRT * SQRT <= N do 
    SQRT := SQRT + 1 ; 
  end ; 

  N:= N + 18;
  SQRT:= SQRT+30;

  if SQRT< N -3 then
  SQRT := N + 10;
  else
  SQRT := N -5; end;
  
  SQRT := SQRT - 1 ;

  writeint SQRT ; 

end 
