# $NetBSD$

DISTNAME=	allswap-cli-validator-1.0.0
CATEGORIES=	security net
MASTER_SITES=	${MASTER_SITE_GITHUB:=1138014573/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://allswap.io/tools/address-validator
COMMENT=	Portable CLI multi-chain cryptocurrency address & memo validator
LICENSE=	mit

USE_LANGUAGES=	c

INSTALLATION_DIRS=	bin

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/allswap-validator ${DESTDIR}${PREFIX}/bin/allswap-validator

.include "../../mk/bsd.pkg.mk"
