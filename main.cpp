#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Iterator {
	virtual void Next()          = 0 ;
	virtual T    Item()    const = 0 ;
	virtual bool HasNext() const = 0 ;
};

template<class T>
struct Iterator_RangeBasedSupport {
	T operator*() const {
		return it->Item() ;
	}
	bool operator!=( const Iterator_RangeBasedSupport& r ) const {
		return it && it->HasNext();
	}
	void operator++() const {
		it->Next();
	}
	Iterator<T>* it ;
};
template<class T>
Iterator_RangeBasedSupport<T> begin( const std::unique_ptr<Iterator<T>>& it ) { return{ it.get()}; }
template<class T>
Iterator_RangeBasedSupport<T> end  ( const std::unique_ptr<Iterator<T>>& it ) { return{ it.get() };/*dummy*/ }

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
std::unique_ptr<Iterator<int>> Nan() { return nullptr; }

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	for ( const auto item : Sequence( 10 ) ) {
		std::cout << item << std::endl;
	}
	for ( const auto item : Nan() ) {}
}
