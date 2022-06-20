#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Iterator {
	virtual void Next()          = 0 ;
	virtual T    Item()    const = 0 ;
	virtual bool HasNext() const = 0 ;
};

namespace impl {

template<class T>
struct Iterator_ {
	T operator*() const {
		return it->Item() ;
	}
	bool operator!=( const Iterator_& r ) const {
		return it && it->HasNext();
	}
	void operator++() const {
		it->Next();
	}
	Iterator<T>* it ;
};

} // impl 
template<class T>
impl::Iterator_<T> begin( const std::unique_ptr<Iterator<T>>& it ) { return{ it.get()}; }
template<class T>
impl::Iterator_<T> end  ( const std::unique_ptr<Iterator<T>>& it ) { return{ nullptr };/*dummy*/ }

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
