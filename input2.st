program test{
	declare a,b,c enddeclare
	
	function f1(in a,inout b,copy c){
		declare n,m,k enddeclare
		
		function f2{
			declare a,b enddeclare
			if(a<b)
				b:=1+3+4+55*7/8-0
			else 
				b:=12
		}
		call f2;
	}
	procedure f3{
	}
	a:=a+a;
	while(a<b)
		a:=b;
		do{
		if(b<a) 
			a:=0
		else 
			b:=0
	}while(not[c>a]);
	
	forcase 
		when (a<c) 
			c:=c-1;
	incase 
		when (a<c) 
			c:=c-1;	
			
	call f1(in a, inout b)
		
	;
	do{
		if(b<a) 
			{
				while(a<b)
					a:=b;
					do{
					if(b<a) 
						a:=0
					else 
						b:=0
				}while(not[c>a]);
				
				forcase 
					when (a<c) 
						c:=c-1;
				incase 
					when (a<c) 
						c:=c-1;	
			}
		else 
			b:=0
	}while(not[c>a]);
	
	forcase 
		when (a<c) 
			c:=c-1;
	incase 
		when (a<c) 
			c:=c-1;	
			
	call f1(in a, inout b)
}