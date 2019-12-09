#include(macros.inc)
[top]
components : mercados

[mercados]
type : cell
dim : (3,3,2)
delay : transport
defaultDelayTime : 1
border : wrapped
neighbors : (-1,-1,0) (-1,0,0) (-1,1,0)
neighbors : (0,-1,0) (0,0,0) (0,1,0)
neighbors : (1,-1,0) (1,0,0) (1,1,0)
neighbors : (-1,-1,1) (-1,0,1) (-1,1,1)
neighbors : (0,-1,1) (0,0,1) (0,1,1)
neighbors : (1,-1,1) (1,0,1) (1,1,1)

%[presupuesto,              % = 1 millon por defecto (1000000)
% precioVenta,              % = $ 2 es el precio inicial
% ofertaTotal,              % = cada uno tiene 10000 de stock
% reposicionOferta,         % = la reposicion actual es de 20 unidades
% crecimientoOferta,        % = -1 -> La demanda supera a la oferta | 1 -> La oferta supera a la demanda | 0 -> Aún no se analizó la variación Oferta-Demanda
% ultimaDemanda,            % = La suma total de demandas satisfechas. Inicial en 0
% interesDeCompra,          % = Autoincremental
% ultimoPrecioCompra,       % = Ultimo precio al que se compro, inicial en 0
% ultimaCantidadComprada,   % = Ultima cantidad de producto comprado, inicial en 0
% quienMeVendio,            % = Ultimo ID de vendedor al que se compró, inicial en 0 (maximo valor: 9999, si la grilla es 100x100)
% id]                       % = Mi propio ID (se carga mediante el archivo mercados.val)
initialvalue : [1000000,2,10000,20,0,0,10,0,0,0,0]
InitialCellsValue : mercados.val

localtransition : reglas-comerciantes

[reglas-comerciantes]
% NOTA: cada unidad de tiempo virtual es un día real, subdivido el tiempo en semanas de 7 dias
% NOTA: En cualquier dia de la semana, si no hay presupuesto, el comerciante desaparece
rule : {(0,0,0)} INF {#macro(noHayPresupuesto)}

% NOTA: Lunes
% Si hay presupuesto, el interes de compra debe subir automaticamente
rule : {#macro(incrementarInteresDeCompra)} 1 {#macro(esLunes)}

% NOTA: Martes
% Si hay presupuesto, se deben actualizar los precios
rule : {#macro(actualizacionDePrecios)} 1 {#macro(esMartes)}

% NOTA: Miercoles
% Si hay presupuesto, se deben actualizar las reposiciones de oferta
rule : {#macro(actualizacionDeReposicionDeOferta)} 1 {#macro(esMiercoles)}

% NOTA: Jueves
% Si no hay interes de compra, no hago nada
rule : {(0,0,0)} 1 {#macro(esJueves) and not #macro(hayInteresDeCompra)}

% Si hay interes de compra, se debe buscar el menor precio de venta e intentar comprar... pero pueden darse 4 casos
% El nuevo minimoPrecioCompra es mas barato que el anterior, y el presupuesto alcanza para satisfacer todo el interesDeCompra
rule : {#macro(compraBarataTotal)} 1 {#macro(esJueves) and #macro(hayInteresDeCompra) and (#macro(minimoPrecioCompra) <= #macro(ultimoPrecioCompra)) and ((#macro(minimoPrecioCompra) * #macro(interesDeCompra)) <= #macro(presupuesto))}

% El nuevo minimoPrecioCompra es mas barato que el anterior pero el presupuesto no alcanza para satisfacer todo el interesDeCompra
rule : {#macro(compraBarataParcial)} 1 {#macro(esJueves) and #macro(hayInteresDeCompra) and (#macro(minimoPrecioCompra) <= #macro(ultimoPrecioCompra)) and ((#macro(minimoPrecioCompra) * #macro(interesDeCompra)) > #macro(presupuesto))}

% El nuevo minimoPrecioCompra es mas caro que el anterior, y el presupuesto alcanza para satisfacer todo el interesDeCompra
rule : {#macro(compraCaraTotal)} 1 {#macro(esJueves) and #macro(hayInteresDeCompra) and (#macro(minimoPrecioCompra) > #macro(ultimoPrecioCompra)) and ((#macro(minimoPrecioCompra) * #macro(interesDeCompra)) <= #macro(presupuesto))}

% El nuevo minimoPrecioCompra es mas caro que el anterior y ademas el presupuesto no alcanza para satisfacer todo el interesDeCompra
rule : {#macro(compraCaraParcial)} 1 {#macro(esJueves) and #macro(hayInteresDeCompra) and (#macro(minimoPrecioCompra) > #macro(ultimoPrecioCompra)) and ((#macro(minimoPrecioCompra) * #macro(interesDeCompra)) > #macro(presupuesto))}

% NOTA: Viernes
% Se atienden los intentos de compra...
rule : {#macro(efectuarCompras)} 1 {#macro(esViernes)}

% NOTA: Fin de Semana
rule : {#macro(incrementarInteresDeCompra)} 2 {#macro(esFinDeSemana)}
