| fullPath selectedIndex |

fullPath := Smalltalk at: #fullPath.

selectedIndex := 1.

FileSystem disk
	filesAt: fullPath
	do: [:absolutePath | | fileStream newStreamFile |
		newStreamFile :=
			(FileSystem disk referenceTo: (fullPath, '/', selectedIndex asString)) writeStream.

		fileStream := FileSystem disk referenceTo: absolutePath.
		fileStream contents linesDo: [:line | | values cellPosition amount tuple times |
			"Si es una linea de interes..."
			(line includesSubstring: ' / Y / ')
				ifTrue: [
					"Subdivido la linea en campos separados por /"
					values := $/ split: line.

					"Si el tiempo es multiplo de 1 año..."
					times := $: split: (values at: 4).
					(((((times at: 3) asString, (times at: 4) asString) asInteger)
						rem: 365) = 0) ifTrue: [
							"Obtengo la tupla de estado"
							tuple := values at: 7.

							"Calculo la posicion de inicio y fin de la tupla"
							start := tuple indexOf: $[.
							end := tuple indexOf: $].

							"Calculo los valores de la tupla"
							size := end - start - 1.
							tuple :=
								$, split: (((String new: size)
									replaceFrom: 1 to: size with: tuple startingAt: start + 1)
										reject: #isSeparator).

							"Solo me interesa el presupuesto"
							amount := tuple first reject: [:char | char isSeparator or: [char = $+ or: [char = $-]]].

							"Convierto el valor a entero"
							amount :=
								((amount indexOf: $e) ~= 0)
									ifTrue: [amount asNumber asInteger asString]
									ifFalse: [
										((amount indexOf: $.) ~= 0)
											ifTrue: [amount at: (amount indexOf: $.) put: $,; yourself]
											ifFalse: [amount asNumber asString]].

							"Obtengo la posicion de la celda"
							cellPosition := (values at: 5) indexOf: $(.

							"Imprimo la linea"
							newStreamFile
								nextPutAll: (values at: 4);
								tab;
								nextPutAll: ((values at: 5) copyFrom: cellPosition to: cellPosition +6);
								tab;
								nextPutAll: amount;
								lf]]].
		newStreamFile close]
