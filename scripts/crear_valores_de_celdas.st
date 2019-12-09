| stream rows cols markets useRandom |

stream := WriteStream on: String new.
rows := 10.
cols := 10.
markets := 2.
useRandom := true.

(0 to: (rows-1)) do: [:currentRow |
	(0 to: (cols-1)) do: [:currentCol |
		(0 to: (markets-1)) do: [:currentMarket |
			stream
				nextPut: $(;
				nextPutAll: currentRow asString;
				nextPut: $,;
				nextPutAll: currentCol asString;
				nextPut: $,;
				nextPutAll: currentMarket asString;
				nextPutAll: ') = '.

			useRandom
				ifTrue: [| randomInt randomSign money price stock supply |
					randomInt := ((SharedRandom globalGenerator next at: 2) asString at: 2) asString asNumber.
					randomSign := ((SharedRandom globalGenerator next at: 2)
						asString at: 3) asString asNumber even ifTrue: [1] ifFalse: [-1].

					money := 1000000 + (randomSign * randomInt * 1000).
					price := 2 + ((randomSign * randomInt * 0.05) roundUpTo: 0.01).
					stock := 10000 + (randomSign * randomInt * 50).
					supply := 20 + (randomSign * randomInt).

					stream
						nextPut: $[;
						nextPutAll: money asString;
						nextPut: $,;
						nextPutAll: price asString;
						nextPut: $,;
						nextPutAll: stock asString;
						nextPut: $,;
						nextPutAll: supply asString;
						nextPutAll: ',0,0,10,0,0,0,']
				ifFalse: [
					stream nextPutAll: '[1000000,2,10000,20,0,0,5,0,0,0,'].
			stream
				nextPutAll: ((currentRow*100)+currentCol) asString;
				nextPut: $];
				lf]]].

stream contents
