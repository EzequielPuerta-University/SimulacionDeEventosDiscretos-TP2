| fullPath |

fullPath := Smalltalk at: #fullPath.

(1 to: 11) do: [:selectedIndex |

FileSystem disk
	filesAt: fullPath
	do: [:absolutePath | | fileStream newStreamFile |
		newStreamFile :=
			((FileSystem disk referenceTo: fullPath) / selectedIndex asString) ensureCreateDirectory.
		newStreamFile := (newStreamFile / absolutePath asPath basename) writeStream.

		fileStream := FileSystem disk referenceTo: absolutePath.
		fileStream contents linesDo: [:line ||start end firstComma size values tempLine|
			start := line indexOf: $[.
			end := line indexOf: $].

			((start+end ~= 0) and: [
				firstComma := line indexOf: $, startingAt: start.
				firstComma > start and: [firstComma < end]]) ifTrue: [
				size := end - start - 1.
				values :=
					$, split: (((String new: size)
						replaceFrom: 1 to: size with: line startingAt: start + 1)
							reject: #isSeparator).

				tempLine :=
					(line copyFrom: 1 to: start-1),
					(values at: selectedIndex),
					(line copyFrom: end+1 to: line size).
				newStreamFile nextPutAll: tempLine; lf]
			ifFalse: [newStreamFile nextPutAll: line; lf]].
		newStreamFile close]]
