| hexColors rgbColors channel cellValues fromIndex toIndex fromValue toValue stream addToStream |

hexColors :=
	OrderedCollection new
		add: 'ffa600';
		add: 'ff9e1b';
		add: 'ff962a';
		add: 'ff8e35';
		add: 'fe873f';
		add: 'fc7f49';
		add: 'fa7752';
		add: 'f8705a';
		add: 'f46962';
		add: 'f0626a';
		add: 'ea5c72';
		add: 'e45779';
		add: 'dc5380';
		add: '945194';
		add: '875192';
		add: '7b518f';
		add: '6f508c';
		add: '634f89';
		add: '574e85';
		add: '4c4d80';
		add: '404b7b';
		add: '354976';
		add: '294770';
		add: '1e446a';
		add: '104263';
		add: '003f5c';
		yourself.

channel := [:color :index | | first last |
	last := 2*index.
	first := last-1.
	(Number readFrom: (color copyFrom: first to: last) base: 16) asString].

rgbColors :=
	(hexColors collect: [:color |
		Array
			with: (channel value: color value: 1)
			with: (channel value: color value: 2)
			with: (channel value: color value: 3)])
		asArray.

cellValues := Interval from: 0.25 to: 6 by: 0.25.
fromIndex := 0.
toIndex := 1.

stream := WriteStream on: String new.
addToStream :=
  [:from :to |
	  stream
	    nextPut: $[;
	    nextPutAll: from;
	    nextPut: $;;
	    nextPutAll: to;
	    nextPut: $];
	    space;
	    nextPutAll: ((rgbColors at: toIndex) at: 1);
	    space;
	    nextPutAll: ((rgbColors at: toIndex) at: 2);
	    space;
	    nextPutAll: ((rgbColors at: toIndex) at: 3);
	    lf].

fromValue := '0'.

[toValue := (cellValues at: toIndex) asString.
addToStream value: fromValue value: toValue]
	doWhileTrue: [
		fromIndex := fromIndex+1.
		toIndex := toIndex+1.
		fromValue := (cellValues at: fromIndex) asString.
		fromIndex < cellValues size].

addToStream value: cellValues last asString value: '1020000'.

stream contents
