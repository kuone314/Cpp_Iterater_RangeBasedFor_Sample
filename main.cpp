#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Iterator {
	virtual void Next()          = 0 ;
	virtual T    Item()    const = 0 ;
	virtual bool HasNext() const = 0 ;
};

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
	for ( auto it = Sequence( 10 ) ; it->HasNext() ; it->Next() ) {
		const auto item = it->Item() ;

		std::cout << item << std::endl;
	}

	
	for ( const auto item : Sequence( 10 ) ) { // ‚±‚Ì—l‚É‘‚«‚½‚¢B
		std::cout << item << std::endl;
	}
}
