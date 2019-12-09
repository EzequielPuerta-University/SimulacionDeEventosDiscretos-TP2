| rawFullPath fullPath newStreamFile |

rawFullPath := Smalltalk at: #fullPath.

(1 to: 11) do: [:attribute |
	fullPath := rawFullPath, attribute asString, '/log01'.
	newStreamFile :=
		(FileSystem disk referenceTo: (rawFullPath, '/', attribute asString, '/', attribute asString))
			writeStream.

	(FileSystem disk referenceTo: fullPath) readStream contents linesDo: [:line | | values cellPosition amount |
		(line includesSubstring: ' / Y / ')
			ifTrue: [
				values := $/ split: line.
				cellPosition := (values at: 5) indexOf: $(.
				amount := (values at: 7) reject: [:char | char isSeparator or: [char = $+ or: [char = $-]]].

				amount :=
					((amount indexOf: $e) ~= 0)
						ifTrue: [amount asNumber asInteger asString]
						ifFalse: [
							((amount indexOf: $.) ~= 0)
								ifTrue: [amount at: (amount indexOf: $.) put: $,; yourself]
								ifFalse: [amount asNumber asString]].

				newStreamFile
					nextPutAll: (values at: 4);
					tab;
					nextPutAll: ((values at: 5) copyFrom: cellPosition to: cellPosition +6);
					tab;
					nextPutAll: amount;
					lf]
			ifFalse: []].
	newStreamFile close]
