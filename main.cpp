#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Iterator {
	virtual void Next()          = 0 ;
	virtual T    Item()    const = 0 ;
	virtual bool HasNext() const = 0 ;
};

struct Iterator_RangeBasedSupport {
	int operator*() const {
		return it->Item() ;
	}
	bool operator!=( const Iterator_RangeBasedSupport& r ) const {
		return it->HasNext();
	}
	void operator++() const {
		it->Next();
	}
	const std::unique_ptr<Iterator<int>>& it ;
};
Iterator_RangeBasedSupport begin( const std::unique_ptr<Iterator<int>>& it ) { return{ it }; }
Iterator_RangeBasedSupport end  ( const std::unique_ptr<Iterator<int>>& it ) { return{ it };/*dummy*/ }

///////////////////////////////////////////////////////////////////////////////////////////////////
std::unique_ptr<Iterator<int>> Sequence( const int limit ) {
	struct Impl :Iterator<int> {
		void Next() override { m_val++ ; }
		int  Item() const override { return m_val ; }
		bool HasNext() const override { return m_val < m_limit ; }

		Impl( const int limit ) :m_limit{ limit } {}
		int m_val = 0 ;
		int m_limit{} ;
	};

	return std::make_unique<Impl>( limit );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	for ( const auto item : Sequence( 10 ) ) {
		std::cout << item << std::endl;
	}
}
