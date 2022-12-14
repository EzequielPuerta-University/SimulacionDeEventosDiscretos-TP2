%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Atributos
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#BeginMacro(presupuesto)
  ((0,0,0)!0)
#EndMacro

#BeginMacro(precioVenta)
  ((0,0,0)!1)
#EndMacro

#BeginMacro(interesDeCompra)
  ((0,0,0)!6)
#EndMacro

#BeginMacro(ultimoPrecioCompra)
  ((0,0,0)!7)
#EndMacro

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Consultas
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Nos permite identificar celdas en grillas de hasta 100x100
% No se usa realmente, ya que se cargan por el archivo mercados.val y no se modifican
% pero queda aca para describir como se debe calcular el id de una celda
% Por ejemplo:  (id: 8542 -> celda: (85,42))
%               (id: 96   -> celda: (0,96))
%               (id: 9999 -> celda: (99,99))
%               (id: 3400 -> celda: (34,0))
#BeginMacro(idCelda)
  (cellpos(0)*100 + cellpos(1))
#EndMacro

#BeginMacro(noHayPresupuesto)
  ((0,0,0)!0 = 0)
#EndMacro

#BeginMacro(hayPresupuesto)
  ((0,0,0)!0 != 0)
#EndMacro

#BeginMacro(hayInteresDeCompra)
  ((0,0,0)!6 > 0)
#EndMacro

#BeginMacro(esLunes)
  (remainder(time,7) = 0)
#EndMacro

#BeginMacro(esMartes)
  (remainder(time,7) = 1)
#EndMacro

#BeginMacro(esMiercoles)
  (remainder(time,7) = 2)
#EndMacro

#BeginMacro(esJueves)
  (remainder(time,7) = 3)
#EndMacro

#BeginMacro(esViernes)
  (remainder(time,7) = 4)
#EndMacro

#BeginMacro(esFinDeSemana)
  ((remainder(time,7) = 5) or (remainder(time,7) = 6))
#EndMacro

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Procesos
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#BeginMacro(incrementarInteresDeCompra)
  [(0,0,0)!0,
   (0,0,0)!1,
   (0,0,0)!2,
   (0,0,0)!3,
   (0,0,0)!4,
   (0,0,0)!5,
   if((0,0,0)!6 < 0, 1,((0,0,0)!6)+2),
   (0,0,0)!7,
   (0,0,0)!8,
   (0,0,0)!9,
   (0,0,0)!10]
#EndMacro

%la demanda supera a la oferta -> aumenta el precio -> disminuye la demanda -> luego aumentara la oferta (o a la inversa)
#BeginMacro(actualizacionDePrecios)
  [(0,0,0)!0,
   if((0,0,0)!5 >= (0,0,0)!3,
    (0,0,0)!1 + (((0,0,0)!1) / 50),
    (0,0,0)!1 - (((0,0,0)!1) / 50)),
   (0,0,0)!2,
   (0,0,0)!3,
   if((0,0,0)!5 >= (0,0,0)!3, -1, 1),
   (0,0,0)!5,
   (0,0,0)!6,
   (0,0,0)!7,
   (0,0,0)!8,
   (0,0,0)!9,
   (0,0,0)!10]
#EndMacro

%si el precio fue aumentado tiempo atras, se debe aumentar la oferta (o a la inversa) (la oferta aumenta o disminuye en 10%)
#BeginMacro(actualizacionDeReposicionDeOferta)
  [(0,0,0)!0,
   (0,0,0)!1,
   ((0,0,0)!2) + if(
      ((0,0,0)!4) < 0,
      ((0,0,0)!3) +10,
      if(
        ((0,0,0)!4) > 0,
        if( (0,0,0)!3 > 5, -5 + ((0,0,0)!3), 0),
        (0,0,0)!3 )),
   if(
      ((0,0,0)!4) < 0,
      ((0,0,0)!3) +10,
      if(
        ((0,0,0)!4) > 0,
        if( (0,0,0)!3 > 5, -5 + ((0,0,0)!3), 0),
        (0,0,0)!3 )),
   0,
   (0,0,0)!5,
   (0,0,0)!6,
   (0,0,0)!7,
   (0,0,0)!8,
   (0,0,0)!9,
   (0,0,0)!10]
#EndMacro

#BeginMacro(compraBarataTotal)
  [(0,0,0)!0 - ((0,0,0)!6) * (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
   (0,0,0)!1,
   (0,0,0)!2,
   (0,0,0)!3,
   (0,0,0)!4,
   (0,0,0)!5,
   (0,0,0)!6,
   min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1),
   (0,0,0)!6,
   if(
    (-1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
      (-1,-1,1)!10,
      if(
       (-1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
         (-1,0,1)!10,
         if(
          (-1,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
            (-1,1,1)!10,
            if(
             (0,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
               (0,-1,1)!10,
               if(
                (0,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                  (0,0,1)!10,
                  if(
                   (0,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                     (0,1,1)!10,
                     if(
                      (1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                        (1,-1,1)!10,
                        if(
                         (1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                           (1,0,1)!10,
                           (1,1,1)!10)))))))),
   (0,0,0)!10]
#EndMacro

#BeginMacro(compraBarataParcial)
  [(0,0,0)!0 - (trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)))) * (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
   (0,0,0)!1,
   (0,0,0)!2,
   (0,0,0)!3,
   (0,0,0)!4,
   (0,0,0)!5,
   (0,0,0)!6,
   min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1),
   trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1))),
   if(
    (-1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
      (-1,-1,1)!10,
      if(
       (-1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
         (-1,0,1)!10,
         if(
          (-1,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
            (-1,1,1)!10,
            if(
             (0,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
               (0,-1,1)!10,
               if(
                (0,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                  (0,0,1)!10,
                  if(
                   (0,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                     (0,1,1)!10,
                     if(
                      (1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                        (1,-1,1)!10,
                        if(
                         (1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                           (1,0,1)!10,
                           (1,1,1)!10)))))))),
   (0,0,0)!10]
#EndMacro

#BeginMacro(compraCaraTotal)
  [(0,0,0)!0 - (-5 + ((0,0,0)!6)) * (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
   (0,0,0)!1,
   (0,0,0)!2,
   (0,0,0)!3,
   (0,0,0)!4,
   (0,0,0)!5,
   -10 + ((0,0,0)!6),
   min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1),
   -5 + ((0,0,0)!6),
   if(
    (-1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
      (-1,-1,1)!10,
      if(
       (-1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
         (-1,0,1)!10,
         if(
          (-1,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
            (-1,1,1)!10,
            if(
             (0,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
               (0,-1,1)!10,
               if(
                (0,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                  (0,0,1)!10,
                  if(
                   (0,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                     (0,1,1)!10,
                     if(
                      (1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                        (1,-1,1)!10,
                        if(
                         (1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                           (1,0,1)!10,
                           (1,1,1)!10)))))))),
   (0,0,0)!10]
#EndMacro

#BeginMacro(compraCaraParcial)
  [(0,0,0)!0 - (if(
     (trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)))) != 0,
     -1 + (trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)))),
     0)) * (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
   (0,0,0)!1,
   (0,0,0)!2,
   (0,0,0)!3,
   (0,0,0)!4,
   (0,0,0)!5,
   -10 + ((0,0,0)!6),
   min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1),
   if(
      (trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)))) != 0,
      -1 + (trunc((0,0,0)!0 / (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)))),
      0),
   if(
    (-1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
      (-1,-1,1)!10,
      if(
       (-1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
         (-1,0,1)!10,
         if(
          (-1,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
            (-1,1,1)!10,
            if(
             (0,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
               (0,-1,1)!10,
               if(
                (0,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                  (0,0,1)!10,
                  if(
                   (0,1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                     (0,1,1)!10,
                     if(
                      (1,-1,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                        (1,-1,1)!10,
                        if(
                         (1,0,1)!1 = (min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)),
                           (1,0,1)!10,
                           (1,1,1)!10)))))))),
   (0,0,0)!10]
#EndMacro

#BeginMacro(efectuarCompras)
  [(0,0,0)!0
    + (if( (-1,-1,1)!9 = (0,0,0)!10 , (-1,-1,1)!7 * (-1,-1,1)!8, 0))
    + (if( (-1,0,1)!9 = (0,0,0)!10 , (-1,0,1)!7 * (-1,0,1)!8, 0))
    + (if( (-1,1,1)!9 = (0,0,0)!10 , (-1,1,1)!7 * (-1,1,1)!8, 0))
    + (if( (0,-1,1)!9 = (0,0,0)!10 , (0,-1,1)!7 * (0,-1,1)!8, 0))
    + (if( (0,0,1)!9 = (0,0,0)!10 , (0,0,1)!7 * (0,0,1)!8, 0))
    + (if( (0,1,1)!9 = (0,0,0)!10 , (0,1,1)!7 * (0,1,1)!8, 0))
    + (if( (1,-1,1)!9 = (0,0,0)!10 , (1,-1,1)!7 * (1,-1,1)!8, 0))
    + (if( (1,0,1)!9 = (0,0,0)!10 , (1,0,1)!7 * (1,0,1)!8, 0))
    + (if( (1,1,1)!9 = (0,0,0)!10 , (1,1,1)!7 * (1,1,1)!8, 0)),
   (0,0,0)!1,
   (0,0,0)!2
     - (if( (-1,-1,1)!9 = (0,0,0)!10 , (-1,-1,1)!8, 0))
     - (if( (-1,0,1)!9 = (0,0,0)!10 , (-1,0,1)!8, 0))
     - (if( (-1,1,1)!9 = (0,0,0)!10 , (-1,1,1)!8, 0))
     - (if( (0,-1,1)!9 = (0,0,0)!10 , (0,-1,1)!8, 0))
     - (if( (0,0,1)!9 = (0,0,0)!10 , (0,0,1)!8, 0))
     - (if( (0,1,1)!9 = (0,0,0)!10 , (0,1,1)!8, 0))
     - (if( (1,-1,1)!9 = (0,0,0)!10 , (1,-1,1)!8, 0))
     - (if( (1,0,1)!9 = (0,0,0)!10 , (1,0,1)!8, 0))
     - (if( (1,1,1)!9 = (0,0,0)!10 , (1,1,1)!8, 0)),
   (0,0,0)!3,
   (0,0,0)!4,
   (if( (-1,-1,1)!9 = (0,0,0)!10 , (-1,-1,1)!8, 0))
     + (if( (-1,0,1)!9 = (0,0,0)!10 , (-1,0,1)!8, 0))
     + (if( (-1,1,1)!9 = (0,0,0)!10 , (-1,1,1)!8, 0))
     + (if( (0,-1,1)!9 = (0,0,0)!10 , (0,-1,1)!8, 0))
     + (if( (0,0,1)!9 = (0,0,0)!10 , (0,0,1)!8, 0))
     + (if( (0,1,1)!9 = (0,0,0)!10 , (0,1,1)!8, 0))
     + (if( (1,-1,1)!9 = (0,0,0)!10 , (1,-1,1)!8, 0))
     + (if( (1,0,1)!9 = (0,0,0)!10 , (1,0,1)!8, 0))
     + (if( (1,1,1)!9 = (0,0,0)!10 , (1,1,1)!8, 0)),
   (0,0,0)!6,
   (0,0,0)!7,
   (0,0,0)!8,
   (0,0,0)!9,
   (0,0,0)!10]
#EndMacro

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Comparaciones con vecinos
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#BeginMacro(minimoPrecioCompra)
  min(min(min(min((-1,-1,1)!1, (-1,0,1)!1), min((-1,1,1)!1, (0,-1,1)!1)), min(min((0,0,1)!1, (0,1,1)!1), min((1,-1,1)!1, (1,0,1)!1))), (1,1,1)!1)
#EndMacro
